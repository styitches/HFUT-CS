def outx():
    n = int(input("请输入参数 n: "))
    a = 1
    b = 1
    x = [1]
    while a < n:
        b += 1
        x.append(a)
        a = x[b-1] + x[b-2]
    return x
print(outx())
