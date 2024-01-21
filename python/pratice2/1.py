import random
import string
num = {}
x = string.digits + string.ascii_letters  #数字加所有字母
y = ""
for i in range(1000):
    y += random.choice(x)       #从x中生成随机的10000个

print(y)
for i in y:
    if num.get(i, "none") == "none":
        num[i] = 1

    else:
        num[i] += 1

print(num)

from random import choices
from string import ascii_letters
from collections import Counter
import string
s = choices(ascii_letters + string.digits, k=1000)
cnt=Counter()
print("list: ", s)
for i in s:
    cnt[i] += 1
print(cnt)
