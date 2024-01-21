x = int(input("请输入一个大于二的自然数："))
a = []
for i in range(2,x):
    for j in range(2,i):
        if i % j ==0:
            break
        if j == i-1:
            a.append(i)
print(a)
