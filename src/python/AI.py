# -*- coding:utf-8 -*-
import time
today=time.localtime()#将本地时间赋值到变量today
print("你好！我是小X。")
"""重复判断"""
while True:
    s=input()
    t=s.replace("吗","")
    t=t.replace("？","！")#将问句转为语气强烈的陈述句
    if "你"in t and"你好"not in t:
        t=t.replace("你","我")
    t=t.replace("谢谢","不用谢")
    t=t.replace("是不是","是")
    if"你的家乡"in s or"住在哪里"in s:
        t="我的家乡在中国。"
    if"你的祖国"in s:
        t="我的祖国是中国，中国很大。"
    if"喜欢什么"in s:
        t="你喜欢的我都喜欢。"
    if"每个人"in s:
        t="是谁？"
    if"小X"in s:
        t="你是在说我吗？"
    if"你能做什么"in s:
        t="为了你，我什么都能做。"
    if "古诗"in t or"唐诗"in t or"诗词"in t:
        t="""我会一首古诗——
    登鹳雀楼
 【唐】王之涣
  白日依山尽，
  黄河入海流。
  欲穷千里目，
  更上一层楼。"""
    if "你好"in t:
        t="你好！很高兴见到你。"
    if"现在时间"in t or"当前时间"in t:
       t=time.strftime("现在时间是%H时%M分%S秒",today).format('时','分','秒')
    if"当前日期"in t or "现在日期"in t:
       t=time.strftime("日期是%Y年%m月%d日",today).format('年','月','日')
    if s==t:
        t="小X还不太聪明，您可以换种说法再试试哦~"
    if "+"in s or"-"in s or"*"in s or"/"in s:
        t=eval(s)
    print(t)
