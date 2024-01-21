x = input("请输入两个首尾交叉的字符串：")
y = input("请输入两个首尾交叉的字符串：")
print("这两个字符串为：")
print(x)
print(y)


def num(x, y):

    a = [i for i in x]
    b = [i for i in y]
    c = []
    flag = 0
    for i in range(len(a)):
        p = a[len(a)-i-1]
        n = len(a)-i-1

        for j in range(len(b)):
            q = b[len(b)-j-1]
            if(flag == 1 and q != p):
                p = a[n+1]
                flag = 0
                c.pop()
            if (q == p):
                flag = 1
                n -= 1
                p = a[n]
                c.append(q)

        break
    num = len(c)
    for i in range(num):
        b.pop(0)

    for i in range(len(a)):
        print(a[i], end=" ")

    for i in range(len(b)):
        print(b[i], end=" ")

(lambda x,y:num(x,y))(x,y)
