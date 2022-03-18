#  -*- coding: utf-8 -*-
import getopt
import os
import platform
import shutil
import subprocess
import sys


class OptionsOfBuild():
    def __init__(self):
        self.pyVer = ''
        self.fileName = ''
        self.rootName = ''
        self.excludeFiles = []
        self.nthread = '1'
        self.quiet = "False"
        self.release = False


isWindows = True if platform.system() == 'Windows' else False

py2sec_version = ('0', '3', '1')

HELP_TEXT = '''
py2sec is a Cross-Platform, Fast and Flexible tool to compile the .py to .so(Linux and Mac) or .pdy(Win).
You can use it to hide the source code of py
It can be called by the main func as "from module import * "
py2sec can be used in the environment of python2 or python3

Usage: python py2sec.py [options] ...

Options:
  -v,  --version    Show the version of the py2sec
  -h,  --help       Show the help info
  -p,  --python     Python version, default is based on the version of python you bind with command "python" 
                    Example: -p 3  (means you tends to encrypt python3)
  -d,  --directory  Directory of your project (if use -d, you encrypt the whole directory)
  -f,  --file       File to be transfered (if use -f, you only encrypt one file)
  -m,  --maintain   List the file or the directory you don't want to transfer
                    Note: The directories should be suffix by path separate char ('\\' in Windows or '/'), 
                    and must be the relative path to -d's value
                    Example: -m setup.py,mod/__init__.py,exclude_dir/
  -x,  --nthread    number of parallel thread to build jobs
  -q   --quiet      Quiet Mode, Default: False
  -r   --release    Release Mode, clear all the tmp files, only output the result, Default: False


Example:
  python py2sec.py -f test.py
  python py2sec.py -f example/test1.py -r
  python py2sec.py -d example/ -m test1.py,bbb/

  # some OS use command "python3" to run python3, like Ubuntu, you can use -p to solve it
  python3 py2sec.py -p 3 -d example/
'''

buildingScript_fileName = 'tmp_py2sec_build.py'
buildingScript_template_fileName = 'py2sec_build.py.template'


def getFiles_inDir(dir_path,
                   includeSubfolder=True,
                   path_type=0,
                   ext_names="*"):
    '''获得指定目录下的所有文件，
        :param dir_path: 指定的目录路径
        :param includeSubfolder: 是否包含子文件夹里的文件，默认 True
        :param path_type: 返回的文件路径形式
            0 绝对路径，默认值
            1 相对路径
            2 文件名
        :param ext_names: "*" | string | list
            可以指定文件扩展名类型，支持以列表形式指定多个扩展名。默认为 "*"，即所有扩展名。
            举例：".txt" 或 [".jpg",".png"]

        :return: 以 yield 方式返回结果

    Updated:
        2020-04-21
    Author:
        nodewee (https://nodewee.github.io)
    '''

    # ext_names
    if type(ext_names) is str:
        if ext_names != "*":
            ext_names = [ext_names]
    # lower ext name letters
    if type(ext_names) is list:
        for i in range(len(ext_names)):
            ext_names[i] = ext_names[i].lower()

    def willKeep_thisFile_by_ExtName(file_name):
        if type(ext_names) is list:
            if file_name[0] == '.':
                file_ext = file_name
            else:
                file_ext = os.path.splitext(file_name)[1]
            #
            if file_ext.lower() not in ext_names:
                return False
        else:
            return True
        return True

    if includeSubfolder:
        len_of_inpath = len(dir_path)
        for root, dirs, files in os.walk(dir_path):
            for file_name in files:
                if not willKeep_thisFile_by_ExtName(file_name):
                    continue
                if path_type == 0:  # absolute path
                    yield os.path.join(root, file_name)
                elif path_type == 1:  # relative path
                    yield os.path.join(
                        root[len_of_inpath:].lstrip(os.path.sep), file_name)
                else:  # filen ame
                    yield file_name
    else:
        for file_name in os.listdir(dir_path):
            filepath = os.path.join(dir_path, file_name)
            if os.path.isfile(filepath):
                #
                if not willKeep_thisFile_by_ExtName(file_name):
                    continue
                #
                if path_type == 0:
                    yield filepath
                else:
                    yield file_name


def makeDirs(dirpath):
    '''
    创建目录
        支持多级目录，若目录已存在自动忽略
        Updated: 2020-02-27
        Author: nodewee (https://nodewee.github.io)
    '''

    dirpath = dirpath.strip().rstrip(os.path.sep)

    if dirpath:
        if not os.path.exists(dirpath):
            os.makedirs(dirpath)


def getCommandOptions(opts):
    try:
        options, _ = getopt.getopt(sys.argv[1:], "vhp:d:f:m:x:qr", [
            "version", "help", "python=", "directory=", "file=", "maintain=",
            "nthread=", "quiet", "release"
        ])
    except getopt.GetoptError:
        print("Get options Error")
        print(HELP_TEXT)
        sys.exit(1)

    for key, value in options:
        if key in ["-h", "--help"]:
            print(HELP_TEXT)
            sys.exit(0)
        elif key in ["-v", "--version"]:
            print("py2sec version {0}".format('.'.join(py2sec_version)))
            sys.exit(0)
        elif key in ["-p", "--python"]:
            opts.pyVer = value
        elif key in ["-d", "--directory"]:
            if opts.fileName:
                print("Canceled. Do not use -d -f at the same time")
                sys.exit(1)
            if value[-1] == '/':
                opts.rootName = value[:-1]
            else:
                opts.rootName = value
        elif key in ["-f", "--file"]:
            if opts.rootName:
                print("Canceled. Do not use -d -f at the same time")
                sys.exit(1)
            opts.fileName = value
        elif key in ["-m", "--maintain"]:
            for path_assign in value.split(","):
                if not path_assign[-1:] in ['/', '\\']:  # if last char is not a path sep, consider it's assign a file
                    opts.excludeFiles.append(path_assign)
                else:  # assign a dir
                    assign_dir = path_assign.strip('/').strip('\\')
                    tmp_dir = os.path.join(opts.rootName, assign_dir)
                    files = getFiles_inDir(dir_path=tmp_dir,
                                           includeSubfolder=True,
                                           path_type=1)
                    #
                    for file in files:
                        fpath = os.path.join(assign_dir, file)
                        opts.excludeFiles.append(fpath)

        elif key in ["-x", "--nthread"]:
            opts.nthread = value
        elif key in ["-q", "--quiet"]:
            opts.quiet = "True"
        elif key in ["-r", "--release"]:
            opts.release = True

    return opts


def getEncryptFileList(opts):
    will_compile_files = []

    #
    if opts.rootName != '':
        if not os.path.exists(opts.rootName):
            print("No such Directory, please check or use the Absolute Path")
            sys.exit(1)

        #
        pyfiles = getFiles_inDir(dir_path=opts.rootName,
                                 includeSubfolder=True,
                                 path_type=1,
                                 ext_names='.py')
        # exclude __init__.py file
        pyfiles = [pyfile for pyfile in pyfiles if not pyfile.endswith('__init__.py')]
        # filter maintain files
        tmp_files = list(set(pyfiles) - set(opts.excludeFiles))
        will_compile_files = []
        for file in tmp_files:
            will_compile_files.append(os.path.join(opts.rootName, file))

    #
    if opts.fileName != '':
        if opts.fileName.endswith(".py"):
            will_compile_files.append(opts.fileName)
        else:
            print("Make sure you give the right name of py file")

    return will_compile_files


def genSetup(opts, will_compile_files):
    if os.path.exists(buildingScript_fileName):
        os.remove(buildingScript_fileName)
    with open(buildingScript_template_fileName, "r") as f:
        template = f.read()
    files = '", r"'.join(will_compile_files)
    cont = template % (files, opts.pyVer, opts.nthread, opts.quiet)
    with open(buildingScript_fileName, "w") as f:
        f.write(cont)


def clearBuildFolders():
    if os.path.isdir("build"):
        shutil.rmtree("build")
    if os.path.isdir("tmp_build"):
        shutil.rmtree("tmp_build")
    if os.path.isdir("result"):
        shutil.rmtree("result")


def clearTmpFiles():
    if os.path.isdir("build"):
        shutil.rmtree("build")
    if os.path.isdir("tmp_build"):
        shutil.rmtree("tmp_build")
    if os.path.isfile("tmp_py2sec_build.py"):
        os.remove("tmp_py2sec_build.py")


def pyEncrypt(opts):
    # prepare folders
    makeDirs('build')
    makeDirs('tmp_build')

    if opts.quiet == "True":
        log = "> log.txt"
    else:
        log = ""
    cmd = " {0} build_ext {1}".format(buildingScript_fileName, log)
    if opts.pyVer == '':
        cmd = 'python' + cmd
    else:
        cmd = 'python' + opts.pyVer + cmd
    if not isWindows:
        print('> pyEncrypt')
        print(cmd)
    p = subprocess.Popen(cmd, shell=True, stderr=subprocess.STDOUT)
    code = p.wait()
    if code:
        print("\nPy2Sec Encrypt Encounter Error")
        sys.exit(1)


def genProject(opts, will_compile_files):
    makeDirs('result')
    for file in getFiles_inDir('build', True, 1, ['.so', '.pyd']):
        src_path = os.path.join('build', file)
        mid_path = os.path.sep.join(file.split(os.path.sep)[1:-1])
        file_name_parts = os.path.basename(src_path).split('.')
        file_name = '.'.join([file_name_parts[0]] + file_name_parts[-1:])
        dest_path = os.path.join('result', mid_path, file_name)
        makeDirs(os.path.dirname(dest_path))
        shutil.copy(src_path, dest_path)
    # 非编译文件靠谱至生成库路径
    not_compile_files = get_not_compile_files(opts, will_compile_files)
    for not_compile_file in not_compile_files:
        dest_path = os.path.join('result', not_compile_file)
        filepath, filename = os.path.split(dest_path)
        makeDirs(filepath)
        shutil.copyfile(not_compile_file, dest_path)

    if opts.release:
        clearTmpFiles()
    print("\nPy2Sec Encrypt Finished")


def get_not_compile_files(opts, will_compile_files):
    """获取非编译文件"""
    files = getFiles_inDir(dir_path=opts.rootName,
                           includeSubfolder=True,
                           path_type=1,
                           ext_names='*')
    files = [os.path.join(opts.rootName, file) for file in files if not file.endswith('.pyc')]
    not_compile_files = list(set(files) - set(will_compile_files))
    return not_compile_files


if __name__ == "__main__":
    opts = getCommandOptions(OptionsOfBuild())
    will_compile_files = getEncryptFileList(opts)
    clearBuildFolders()
    if not isWindows:
        genSetup(opts, will_compile_files)
        pyEncrypt(opts)
    else:  # Windows OS
        for file in will_compile_files:
            genSetup(opts, [file])
            pyEncrypt(opts)

    genProject(opts, will_compile_files)