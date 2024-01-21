k = ['do', 'end', 'for', 'if', 'printf', 'scanf', 'then', 'while']  # 关键字表 1
s = ['+', '-', '*', '/']  # 算术运算符：+、-、*、/；   3
r = [';', ',', '(', ')', '[', ']', '']  # 分界符： ；、，、（、）、[、]； 2
t = ['<', '<=', '=', '>', '>=', '<>']  # 关系运算符： <、<=、= 、>、>=、<>； 4
u = []  # 常数表         5
v = []  # 标识符表       6
tep = '    '  # 用于控制输出信息之间的距离
hang = 1  # 保存当前单词的行数
lie = 1  # 保存当前单词的列数
output = []  # 用于保存输出信息
jud1 = 0  # 判断当前内容是否为注释，为1表示为注释的内容
for line in open("test.txt", 'r', encoding="UTF-8"):
    str = line
    i = 0
    while i < len(str):
        if jud1 != 1:
            if str[i].isdigit():  # 字符为数字
                jud = 1  # 用于判断该单词是不是纯数字
                str1 = ''  # 用于暂时存储单词
                while i < len(str):
                    if str[i].isdigit():
                        str1 += str[i]
                        i += 1
                    elif str[i].isalpha():
                        str1 += str[i]
                        i += 1
                        jud = 0
                    else: break
                if jud == 1:  # 全为数字，构建输出
                    if str1 in u: u.append(str1)
                    mes = [str1, f'(1,{str1})', '常数', f'({hang},  {lie})']
                else:  # 夹杂有字母
                    mes = [str1, 'Error', 'Error', f'({hang},  {lie})']
                lie += 1
                message = tep.join(mes)
                output.append(message)
            elif str[i].isalpha():  # 字符为字母
                str1 = ""
                while i < len(str):
                    if str[i].isdigit() or str[i].isalpha():
                        str1 += str[i]
                        i += 1
                    else: break
                if str1 in k:
                    mes = [str1, f'(1,{str1})', '关键字', f'({hang},  {lie})']
                elif not str1 in v:
                    v.append(str1)
                    mes = [str1, f'(6,{str1})', '标识符', f'({hang},  {lie})']
                else:
                    mes = [str1, f'(6,{str1})', '标识符', f'({hang},  {lie})']
                lie += 1
                message = tep.join(mes)
                output.append(message)
            elif (str[i] in s):  # 字符为算术运算符
                str1 = ""
                if str[i] == '/' and str[i+1] == '/':
                    i = len(str)
                elif str[i] == '/' and str[i+1] == '*':
                    jud1 = 1
                else:
                    while i < len(str):
                        if str[i] in s:
                            str1 += str[i]
                            i += 1
                        else: break
                    if str1 in s:
                        mes = [str1, f'(1,{str1})', '算术运算符', f'({hang},  {lie})']
                    else:
                        mes = [str1, 'Error', 'Error', f'({hang},  {lie})']
                    lie += 1
                    message = tep.join(mes)
                    output.append(message)
            elif (str[i] in t):  # 字符为关系运算符
                str1 = ""
                while i < len(str):
                    if str[i] in t:
                        str1 += str[i]
                        i += 1
                    else: break
                if str1 in t: mes = [str1, f'(1,{str1})', '关系运算符', f'({hang},  {lie})']
                else: mes = [str1, 'Error', 'Error', f'({hang},  {lie})']
                lie += 1
                message = tep.join(mes)
                output.append(message)
            elif (str[i] in r):  # 字符为分界符
                str1 = str[i]
                i += 1
                mes = [str1, f'(1,{str1})', '分界符', f'({hang},  {lie})']
                lie += 1
                message = tep.join(mes)
                output.append(message)
            elif (str[i] == ' '): i += 1  #字符为空格
            elif (str[i] == '\n'):
                hang += 1
                i += 1
                continue
            else:
                i += 1
                mes = [str1, 'Error', 'Error', f'({hang},  {lie})']
                lie += 1
                message = tep.join(mes)
                output.append(message)
        else:
            while str[i] != '*' or str[i+1] != '/':
                if (i < len(str)-2):
                    i += 1
                else: break
            if str[i] == '*' or str[i+1] == '/':
                jud1 = 0
                hang -= 1
                i += 2
            else: break
for i in output:
    print(i)