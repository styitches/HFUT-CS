import random
a = int(input("请输入参数n: "))
m = 0
y = []
x = [random.randint(1, 1000) for i in range(a)]
for i in range(len(x)):
    m += x[i]
s = m / len(x)
print("平均值为:", s)
y.append(s)
for i in range(len(x)):
    if s < x[i]:
        y.append(x[i])
z = tuple(y)
print(x)
print(z)
