def func(x,y):
    a = []
    num = 0
    for i in range(y):
        if i % 2 !=0:
            a.append(i)
            num +=1

        if num >= x:
            break

    return a


x = int(input("请输入元素个数X: "))
y = int(input("请输入元素最大不超过y: "))
g = tuple(func(x,y))

a = lambda x, y: func(x,y)
print(g)
