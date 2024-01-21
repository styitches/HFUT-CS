import re


def check(str):
    list1 = str.split(",")
    for str in list1:
        if not 6 < len(str) < 12:
            print("长度范围在6与12之外")
            list1[list1.index(str)] = 0
            break

        PassWordCheck = re.compile(r"[0-9]")
        judge = PassWordCheck.search(str)
        if judge is None:
            print("您输入的密码没有带数字")
            list1[list1.index(str)] = 0
            break

        PassWordCheck = re.compile(r"[a-z]")
        judge = PassWordCheck.search(str)
        if judge is None:
            print("您输入的密码没有带小写字母")
            list1[list1.index(str)] = 0
            break

        PassWordCheck = re.compile(r"[A-Z]")
        judge = PassWordCheck.search(str)
        if judge is None:
            print("您输入的密码没有带大写字母")
            list1[list1.index(str)] = 0
            break

        PassWordCheck = re.compile(r"[@#$]")
        judge = PassWordCheck.search(str)
        if judge is None:
            print("您输入的密码没有带特殊符号")
            list1[list1.index(str)] = 0
            break

    for i in list1:
        if i != 0:
            print(i)

check("Cc12#111, 1233444444, 1a#@asA123")
