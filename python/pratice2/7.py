import re
A = input("请输入一段英文： ")
B = [i for i in (re.split('[\. ]+',A))]
for i in B:
    if len(i) == 3:
        print(i)