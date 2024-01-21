letter = input("请输入任意长度的字符串： ")
a = []
b = []
c = []
flag = 0
for i in (letter.split()):
   a.append(i)
print(a)
for i in range(len(a)):
    flag = 0
    if len(b) == 0:
        b.append(a[0])
        c.append(1)
    for j in range(len(b)):
        if a[i] == b[j]:
            c[j] += 1
            flag = 1
    if flag == 0:
        b.append(a[i])
        c.append(1)
        flag = 1

G = dict(zip(b, c))
print(G)
