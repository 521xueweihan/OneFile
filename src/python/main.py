import time
import os
import watchdog
from watchdog.observers import Observer
from watchdog.utils.dirsnapshot import DirectorySnapshot, DirectorySnapshotDiff
import sys
import threading
import tarfile

class HD(watchdog.events.FileSystemEventHandler):
    def __init__(self, aim_path):
        super().__init__()
        self.timer = None
        self.aim_path = aim_path
        self.snapshot = DirectorySnapshot(self.aim_path)
        self.second = 120

    def checkSnapshot(self):
        snapshot = DirectorySnapshot(self.aim_path)
        diff = DirectorySnapshotDiff(self.snapshot, snapshot)
        self.snapshot = snapshot
        self.timer = None
        if not os.path.exists("./backup"):
            os.mkdir("./backup")
        tar_file = tarfile.open('./backup/%s.tar.gz' % (time.strftime('%Y-%m-%d-%H-%M-%S',time.localtime())),'w')
        for x in diff.files_modified:
            # print(x)
            tar_file.add(x)
        tar_file.close()

    def on_modified(self, event):
        if self.timer:
            self.timer.cancel()
        self.timer = threading.Timer(120, self.checkSnapshot)
        self.timer.start()

def observe(path="", timer=120):
    observer = Observer()
    observer.start()
    event_handler = HD(path)
    event_handler.second = timer
    observer.schedule(event_handler, path, recursive=True)
    try:
        while True:
            time.sleep(timer)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()

if __name__ == '__main__':
    observe(path=sys.argv[1], timer=int(sys.argv[2]))