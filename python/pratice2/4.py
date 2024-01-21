import random
a = []
for i in range(0,20):
    x = random.randint(0,100)
    a.append(x)
c = []

e = []

d = a[::-1]
print(d)
for i in range(0,len(a)):
    if(i % 2 == 0):
        e.append(a[i])

num = []
num.append(a)  #新列表
num.append(d)  #逆序列表
num.append(e)  #偶数位置列表
print(num)
