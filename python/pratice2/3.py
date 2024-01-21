import random
import string
N =int(input("请输入你想输入的字符串的个数N："))
M = int(input("请输入你想输入字符串的最大长度M： "))
a = []
num = []
for i in range(N):
    letter = random.sample(string.digits + string.ascii_letters,M)
    a = ""
    for i in letter:
        a = a + i

    print(a)
    i = []
    i.append(a)
    num.append(i)
print(num)
for i in range(len(num)):
    for j in range(i, len(num)):
        temp = num[i]
        if num[i] < num[j]:
            num[i] = num[j]
            num[j] = temp


print(num)
