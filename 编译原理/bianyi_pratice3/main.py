import wx
import wx.xrc

# ------全局变量------#
FIRST = dict()  # FIRST集
ITER_SET = list()  # 项目集族
LAN = dict()  # 文法
LAN1 = dict()  # 带标号的文法
VT = set()  # 终结符
VN = set()  # 非终结符
V = set()  # 符号表
GOTO = list()  # GOTO函数
ACTION = list()  # ACTION函数
Table = list()  # 分析表
ProcessList = dict()  # 缓存列表
ProcessList1 = dict()  # FIRST缓存列表
Table_ProcessList = list()  # 分析表缓存列表


class Grammar:  #项目定义
    def __init__(self):
        self.A = ''  # 产生式左部
        self.B = ''  # 产生式右部
        self.parm = list()  # 后缀（展望）
        self.key = 0  # .位置

    def out(self): #输出产生式
        if (self.key == 0):#圆点的位置在最开始
            print(self.A + "->." + self.B + ',', end='')
        else:
            print(self.A + "->" + self.B[0:self.key] + '.' + self.B[self.key:] + ',', end='')
        print(self.parm)#输出展望

    def in_parm(self, str):  # 添加后缀
        self.parm.extend(str)#在parm中加入str
        self.parm = self.Distinct(self.parm)#去重

    def in_AB(self, str1, str2):  # 加入产生式
        self.A = str1
        self.B = str2

    def get_Next(self):  # 获取下一项目左部
        if (self.key < len(self.B)):
            return self.B[self.key]
        else:
            return 'S1'

    def get_Frist(self):  # 求FIRSR（βa），返回一个后缀列表
        parm1 = list()
        if (self.key != len(self.B) - 1):  # 判断β是否存在，如果不存在，就返回现有后缀
            if (self.B[self.key + 1].isupper()):  # 如果为大写字母
                parm1.extend(FIRST[self.B[self.key + 1]])
                if ('$' in FIRST[self.B[self.key + 1]]):  # 如果后缀含有空字，则加入现有后缀
                    parm1.extend(self.parm)
            else:
                parm1.append(self.B[self.key + 1])
        else:
            parm1.extend(self.parm)
        parm1 = self.Distinct(parm1)
        return parm1

    def Distinct(self, parm1): #去重
        lt = []
        for i in parm1:
            if i not in lt:
                lt.append(i)
        return lt

    def clear(self): #清空产生式
        self.A = ''  # 产生式左部
        self.B = ''  # 产生式右部
        self.parm.clear()  # 参数
        self.key = 0  # .位置



class project:  #项目集定义
    def __init__(self):
        self.grammar = list()  # 产生式集合,存储形式为Grammar
        self.I = 0

    def in_I(self, num):  # 返回现有项目集标号
        self.I = num

    def judge_equal(self, g):  # 判断产生式是否已经在当前项目集中(对于核心相同的时候，就直接加入到当前项目集后缀)
        for S in self.grammar:
            if ((g.A == S.A) and (g.B == S.B) and (g.key == S.key)):
                if not (set(g.parm).issubset(set(S.parm))):  # 合并产生式，将核心相同的产生式的后缀合并
                    S.parm.extend(g.parm)
                    S.parm = S.Distinct(S.parm)  # 去重
                return False #核心相同
        return True #不存在

    def judge_equal1(self, g):  # 判断产生式是否已经在当前项目集中
        for S in self.grammar:
            if ((g.A == S.A) and (g.B == S.B)and (g.key == S.key)):
                if (set(g.parm).issubset(set(S.parm))) and (set(S.parm).issubset(set(g.parm))):  # 核心与后缀完全相等
                    return True #已存在
        return False #之前不存在

    def judge_project(self, project1): # 判断两个项目集是否相同
        if (len(project1.grammar) != len(self.grammar)):  # 如果项目集元素数不相同，则说明这两个项目集不相同
            return False
        for L in project1.grammar:  # 循环判断中所有的产生式属于当前项目集
            if not (self.judge_equal1(L)):
                return False
        return True #两个项目集相同

    def is_empty(self):  # 判断项目集是否为空
        if len(self.grammar) == 0:
            return True
        else:
            return False

    def CLOSURE(self): # 构建当前项目集闭包
        i = 0
        while (i < len(self.grammar)):  # 不断循环直到项目集不再变化为止
            str = self.grammar[i].get_Next()  # 获取下一产生式左部
            if (str.isupper()) and (str != 'S1'):
                for L in LAN[str]:  # 循环加入所有不同的产生式
                    g = Grammar() #生成一个产生式
                    g.in_AB(str, L)
                    g.in_parm(self.grammar[i].get_Frist()) #由上一个产生式来决定该产生式的后缀
                    if (self.judge_equal(g)):
                        self.get_Grammar(g)
            i += 1

    def OUT_CLOSURE(self):  # 输出当前项目集闭包
        print("项目" + str(self.I) + ':')
        for L in self.grammar:
            L.out()

    def get_Grammar(self, grammar1):    # 添加一个产生式
        self.grammar.append(grammar1)

    def Next_CLOSURE(self, str):    # 构造下一项目集,str为读入符号,移进
        Next_CLO = project()
        for L in self.grammar:  # 循环当前项目集的所有产生式，将符合读入符号的项目全部加入到下一项目集中，返回一个并没有完成闭包的下一项目集
            if (L.key < len(L.B)): #标点未到最后
                if (L.B[L.key] == str):
                    g = Grammar()
                    g.in_AB(L.A, L.B)
                    g.key = L.key + 1 #标点右移一位
                    g.in_parm(L.parm)
                    if (Next_CLO.judge_equal(L)):
                        Next_CLO.grammar.append(g)
        return Next_CLO


class MyFrame1(wx.Frame):    # 窗口设计
    def __init__(self, parent):
        wx.Frame.__init__(self, parent, id=wx.ID_ANY, title=u"LL(1)文法分析器", pos=wx.DefaultPosition,
                          size=wx.Size(500, 900),
                          style=wx.CAPTION | wx.CLOSE_BOX | wx.MINIMIZE_BOX | wx.MAXIMIZE | wx.DEFAULT_FRAME_STYLE | wx.SYSTEM_MENU | wx.TAB_TRAVERSAL,
                          name=u"Main")

        self.SetSizeHintsSz(wx.DefaultSize, wx.DefaultSize)
        self.SetForegroundColour(wx.SystemSettings.GetColour(wx.SYS_COLOUR_BTNTEXT))
        self.SetBackgroundColour(wx.SystemSettings.GetColour(wx.SYS_COLOUR_WINDOW))
        bSizer1 = wx.BoxSizer(wx.VERTICAL)  # 构造横向
        bSizer2 = wx.BoxSizer(wx.HORIZONTAL)
        bSizer2.Add(bSizer1, 0, wx.EXPAND, 5)
        bSizer10 = wx.BoxSizer(wx.VERTICAL)
        bSizer2.Add(bSizer10, 0, wx.EXPAND, 5)
        bSizer11 = wx.BoxSizer(wx.HORIZONTAL)

        fgSizer2 = wx.FlexGridSizer(0, 2, 0, 0)
        fgSizer2.SetFlexibleDirection(wx.BOTH)
        fgSizer2.SetNonFlexibleGrowMode(wx.FLEX_GROWMODE_SPECIFIED)

        self.m_staticText3 = wx.StaticText(self, wx.ID_ANY, u"请选择文法文件的位置", wx.DefaultPosition, wx.DefaultSize, 0)
        self.m_staticText3.Wrap(-1)
        self.m_staticText3.SetFont(wx.Font(wx.NORMAL_FONT.GetPointSize(), 70, 90, 90, False, wx.EmptyString))

        fgSizer2.Add(self.m_staticText3, 0, wx.ALL, 5)
        self.m_filePicker1 = wx.FilePickerCtrl(self, wx.ID_ANY, wx.EmptyString, u"Select a file", u"*.*",
                                               wx.DefaultPosition, wx.Size(300, -1),
                                               wx.FLP_DEFAULT_STYLE | wx.FLP_SMALL)
        fgSizer2.Add(self.m_filePicker1, 0, wx.ALL, 5)
        bSizer1.Add(fgSizer2, 0, wx.EXPAND, 5)

        fgSizer4 = wx.FlexGridSizer(0, 3, 0, 0)
        fgSizer4.SetFlexibleDirection(wx.BOTH)
        fgSizer4.SetNonFlexibleGrowMode(wx.FLEX_GROWMODE_SPECIFIED)
        self.m_staticText4 = wx.StaticText(self, wx.ID_ANY, u"请输入要分析的字符串", wx.DefaultPosition, wx.DefaultSize, 0)
        self.m_staticText4.Wrap(-1)
        fgSizer4.Add(self.m_staticText4, 0, wx.ALL, 5)
        self.m_textCtrl3 = wx.TextCtrl(self, wx.ID_ANY, wx.EmptyString, wx.Point(-1, -1), wx.Size(200, -1), 0)
        str = self.m_textCtrl3.GetValue()
        fgSizer4.Add(self.m_textCtrl3, 0, wx.ALL, 5)

        self.m_button3 = wx.Button(self, wx.ID_ANY, u"分析", wx.DefaultPosition, wx.DefaultSize, 0)
        fgSizer4.Add(self.m_button3, 0, wx.ALL, 5)
        bSizer1.Add(fgSizer4, 0, wx.EXPAND, 5)

        fgSizer5 = wx.FlexGridSizer(0, 1, 0, 0)
        fgSizer5.SetFlexibleDirection(wx.BOTH)
        fgSizer5.SetNonFlexibleGrowMode(wx.FLEX_GROWMODE_SPECIFIED)

        # FIRST链表框
        self.m_ListCtrl1 = wx.ListCtrl(self, -1, style=wx.LC_REPORT, size=wx.Size(600, 300))
        self.m_ListCtrl1.InsertColumn(0, "FIRST")
        self.m_ListCtrl1.InsertColumn(1, "内容")
        fgSizer5.Add(self.m_ListCtrl1, 0, wx.ALL, 5)

        # 分析过程链表框
        self.m_ListCtrl3 = wx.ListCtrl(self, -1, style=wx.LC_REPORT, size=wx.Size(600, 450))
        self.m_ListCtrl3.InsertColumn(0, "步骤")
        self.m_ListCtrl3.InsertColumn(1, "分析栈")
        self.m_ListCtrl3.InsertColumn(2, "剩余输入串")
        self.m_ListCtrl3.InsertColumn(3, "所用产生式")
        self.m_ListCtrl3.InsertColumn(4, "动作")
        fgSizer5.Add(self.m_ListCtrl3, 0, wx.ALL, 5)

        # ACTION和GOTO
        bSizer4 = wx.BoxSizer(wx.VERTICAL)
        Lable1 = wx.StaticText(self, -1, '状态', pos=wx.DefaultPosition,
                               size=wx.DefaultSize, style=wx.ALIGN_CENTER)
        self.m_ListCtrl4 = wx.ListCtrl(self, -1, style=wx.LC_REPORT, size=wx.Size(50, 900))
        self.m_ListCtrl4.InsertColumn(0, "                ")
        bSizer4.Add(Lable1, 0, wx.EXPAND, 5)
        bSizer4.Add(self.m_ListCtrl4, 0, wx.EXPAND, 5)
        bSizer11.Add(bSizer4, 0, wx.EXPAND, 0)

        bSizer5 = wx.BoxSizer(wx.VERTICAL)
        Lable2 = wx.StaticText(self, -1, 'ACTION', pos=wx.DefaultPosition,
                               size=wx.DefaultSize, style=wx.ALIGN_CENTER)
        self.m_ListCtrl5 = wx.ListCtrl(self, -1, style=wx.LC_REPORT, size=wx.Size(400, 900))
        bSizer5.Add(Lable2, 0, wx.EXPAND, 5)
        bSizer5.Add(self.m_ListCtrl5, 0, wx.EXPAND, 5)
        bSizer11.Add(bSizer5, 0, wx.EXPAND, 0)

        bSizer6 = wx.BoxSizer(wx.VERTICAL)
        Lable3 = wx.StaticText(self, -1, 'GOTO', pos=wx.DefaultPosition,
                               size=wx.DefaultSize, style=wx.ALIGN_CENTER)
        self.m_ListCtrl6 = wx.ListCtrl(self, -1, style=wx.LC_REPORT, size=wx.Size(200, 900))
        self.m_ListCtrl6.InsertColumn(0, "   ")
        bSizer6.Add(Lable3, 0, wx.EXPAND, 5)
        bSizer6.Add(self.m_ListCtrl6, 0, wx.EXPAND, 5)
        bSizer11.Add(bSizer6, 0, wx.EXPAND, 0)

        Lable4 = wx.StaticText(self, -1, 'LR1分析表', pos=wx.DefaultPosition,
                               size=wx.DefaultSize, style=wx.ALIGN_CENTER)
        bSizer10.Add(Lable4, 0, wx.EXPAND, 0)
        bSizer10.Add(bSizer11, 0, wx.EXPAND, 0)

        bSizer1.Add(fgSizer5, 0, wx.EXPAND, 5)
        self.SetSizer(bSizer2)
        self.Layout()
        self.Centre(wx.BOTH)
        self.m_button3.Bind(wx.EVT_BUTTON, self.m_button3OnButtonClick)  # 对点击button按钮事件处理

    def get_LAN(self):    # 从文件中获取文法
        file_path = self.m_filePicker1.GetPath()
        fo = open(file_path, "r")  # 读文法文件
        i = 0
        for line in fo.readlines():
            if (i == 0):
                LAN1['0'] = 'S1->' + line[3] #line[3]为产生式右边首字符
                LAN['S1'] = line[3]
                i = 1
            splitlist = line[6:].replace("\n", "").split("|")  # 去除空格与换行符,切割字符串,？？？？
            if (line[3] in LAN.keys()):  #该字符之前已经是文法的键
                LAN[line[3]] += splitlist
            else:
                LAN[line[3]] = splitlist
            if line[3].isupper() :
                VN.add(line[3])
            else :
                VT.add(line[3])

            V.add(line[3])

            LAN1[line[1]] = line[3:].replace("\n", "")
        for L in LAN1:
            print(L)
            print(LAN1[L])

    def judge_ITER_SET(self, Project): # 判断当前生成项目集是否在原项目集族中，是则返回相同项目集标号，不是，则返回-1
        for x in ITER_SET:
            if Project.judge_project(x):
                return x.I
        return -1

    def get_ITER_SET(self):   # 获得项目集族与GOTO函数与ACTION中移进操作,不包括归约
        Project = project()
        i = 1  # 新项目集标号
        j = 0  # 当前项目集标号
        # n = 0

        Project.in_I(0)# 初始是特别先进行一次操作
        g = Grammar()
        g.in_AB('S1', LAN['S1'])
        g.in_parm('#')
        Project.get_Grammar(g)
        Project.CLOSURE()
        ACTION.append(dict())
        GOTO.append(dict())
        ITER_SET.append(Project)
        ITER_SET[0].OUT_CLOSURE() #输出
        while (j < len(ITER_SET)):
            for s in V:
                Next_CLO = project()
                Next_CLO = ITER_SET[j].Next_CLOSURE(s)
                if (Next_CLO.is_empty()):  # 如果项目集为空，则直接考虑下一输入
                    continue
                Next_CLO.CLOSURE()  # 构造闭包
                Next_CLO.in_I(i)  #项目集编号
                a = self.judge_ITER_SET(Next_CLO)
                if (a == -1):  # 如果为新的状态
                    ITER_SET.append(Next_CLO)
                    ITER_SET[-1].OUT_CLOSURE() #输出项目
                    ACTION.append(dict())
                    GOTO.append(dict())
                    if (s.isupper()):  # 如果为大写字母，则代表为GOTO函数，更新GOTO函数
                        GOTO[j][s] = str(i)
                    else:  # 如果遇到小写字母，则代表其为ACTION，更新ACTION函数
                        ACTION[j][s] = 's' + str(i)
                    i += 1
                else:  # 如果不为新状态，则代表当前项目集在遇到当前字符时进入到过去已经有的状态中，那么则更新ACTION与GOTO函数就通过返回的状态号来实现
                    if (s.isupper()):
                        GOTO[j][s] = str(a)
                    else:
                        ACTION[j][s] = 's' + str(a)

            j += 1
        # 至此，GOTO函数已经完成，ACTION函数还有部分没有完成

    def get_ACTION(self): # 构造ACTION函数剩余部分，即规约项目
        i = ''
        j = 0
        for Project in ITER_SET:
            for L in Project.grammar:
                if (L.key == len(L.B)):  # 规约项目
                    for k in LAN1:
                        if (LAN1[k] == (L.A + '->' + L.B)):
                            i = k
                            break
                    for s in L.parm:
                        if (L.A == 'S1' and s == '#'):
                            ACTION[j][s] = 'acc'
                        else:
                            ACTION[j][s] = 'r' + i
            j += 1

    def get_first(self): # 获取FIRST集
        for k in LAN:
            l = LAN[k]
            FIRST[k] = list()
            for s in l:
                if not (s[0].isupper()):  # 如果该字符串的首字符并非大写字母，则为加入当前非终结符的FIRST中
                    FIRST[k].append(s[0])
        i = True
        while (i):
            i = False
            for k in LAN:
                l = LAN[k]
                for s in l:
                    if (s[0].isupper()):
                        if not (set(FIRST[s[0]]).issubset(set(FIRST[k]))):
                            FIRST[k].extend(FIRST[s[0]])
                            FIRST[k] = list(set(FIRST[k]))
                            i = True
        for x in FIRST:  # 去重
            FIRST[x] = list(set(FIRST[x]))
            print(x + ':', end='')
            print(FIRST[x])

        count = 1
        ProcessList1.clear()  # 输出列表
        for key, value in FIRST.items():
            ProcessList1[count] = ('FIRST(' + str(key) + ')', str(value))
            count += 1

        self.m_ListCtrl1.DeleteAllItems()  # 清除表中内容（不清除表头）
        for key, data in ProcessList1.items():
            index = self.m_ListCtrl1.InsertItem(self.m_ListCtrl1.GetItemCount(), str(key))
            self.m_ListCtrl1.SetItem(index, 0, data[0])
            self.m_ListCtrl1.SetItem(index, 1, data[1])
            self.m_ListCtrl1.SetColumnWidth(0, 80)
            self.m_ListCtrl1.SetColumnWidth(1, 420)

    def get_VT(self):# 获取终结符、非终结符，与所有符号
        VT.add('#')
        V.add('#')
        for l in LAN.values():
            for s in l:
                for c in s:
                    if not (c.isupper()) and (c != '$'):
                        VT.add(c)
                        V.add(c)
        count = 0
        for s in VT:
            self.m_ListCtrl5.InsertColumn(count, s)
            count += 1

        count = 0
        for s in VN:
            self.m_ListCtrl6.InsertColumn(count, s)
            count += 1

    def get_Table(self):    # 获取分析表
        i = 0
        for i in range(0, len(ITER_SET)):
            d = dict()
            d.update(ACTION[i])
            d.update(GOTO[i])
            Table.append(d)
        i = 0
        for L in Table:
            print(str(i) + ':', end="")
            print(L)
            i += 1

        L = 0
        for i in Table:
            x = list()
            for s in VT:
                if (s in Table[L]): #？？？？
                    x.append(Table[L][s])
                else:
                    x.append('error')
            for s in VN:
                if (s in Table[L]):
                    x.append(Table[L][s])
                else:
                    x.append('error')
            Table_ProcessList.append(x)
            L += 1

        L = 0
        for key in Table_ProcessList:
            index = self.m_ListCtrl4.InsertItem(self.m_ListCtrl4.GetItemCount(), str(key))
            print(index)
            self.m_ListCtrl4.SetItem(index, 0, str(L))
            self.m_ListCtrl6.SetColumnWidth(0, 40)

            count = 0
            index = self.m_ListCtrl5.InsertItem(self.m_ListCtrl5.GetItemCount(), str(key))
            for s in VT:
                self.m_ListCtrl5.SetItem(index, count, Table_ProcessList[L][count])
                self.m_ListCtrl5.SetColumnWidth(count, 60)
                count += 1

            i = 0
            index = self.m_ListCtrl6.InsertItem(self.m_ListCtrl6.GetItemCount(), str(key))
            for s in VN:
                self.m_ListCtrl6.SetItem(index, i, Table_ProcessList[L][count])
                self.m_ListCtrl6.SetColumnWidth(i, 60)
                count += 1
                i += 1
            L += 1

    def judge(self, current2): #判断项目集里是否有空集
        Project = ITER_SET[current2]
        for i in Project.grammar:
            if(i.B=='$'): #找到空集
                return True
        return False


    def analyze(self):  # 分析过程
        inputstr = self.m_textCtrl3.GetValue()  # 输入任意字符串
        inputstr = list(inputstr)
        print(inputstr)
        state = list()  # 表示状态栈
        state.append('0')
        process = list()  # 表示符号栈
        process.append('#')  # "#"入栈
        count = 0  # 插入列表时的索引
        error = 1
        ProcessList.clear()
        ProcessList[count] = (0, ''.join(state), ''.join(process), ''.join(inputstr), '初始')
        while (True):
            count += 1
            current1 = process[-1] #取最后一个元素
            current2 = int(state[-1])

            if (inputstr[0] in Table[current2]):  # 如果存在操作
                if (Table[current2][inputstr[0]][0] == 's'):  # 遇到移进操作，即根据分析表，遇到‘si’
                    state.append(Table[current2][inputstr[0]][1:])
                    process.append(inputstr[0])
                    inputstr.pop(0)
                    ProcessList[count] = (count, ''.join(state), ''.join(process), ''.join(inputstr),
                                          ('ACTION[' + str(current2) + ',' + process[-1] + ']=' + Table[current2][
                                              process[-1]] + '状态' + str(Table[current2][process[-1]][1]) + '入栈'))

                elif (Table[current2][inputstr[0]] == 'acc'):  # 成功标志
                    ProcessList[count] = (count, ''.join(state), ''.join(process), ''.join(inputstr), 'Acc分析成功')
                    break
                elif (Table[current2][inputstr[0]][0] == 'r'):  # 归约操作，即根据分析表，遇到‘ri’
                    op = Table[current2][inputstr[0]]
                    str1 = LAN1[Table[current2][inputstr[0]][1]] #获得对应的标号文法
                    print("".join(process[-(len(str1) - 3):]))
                    if (str1[3:] == "".join(process[-(len(str1) - 3):])): #比较产生式右部
                        for x in range(0, (len(str1) - 3)):
                            process.pop() #删除旧数据
                            state.pop()
                        process.append(str1[0]) #更新新数据
                        state.append(Table[int(state[-1])][process[-1]])

                        if (inputstr[0] in Table[int(state[-1])]):
                            ProcessList[count] = (count, ''.join(state), ''.join(process), ''.join(inputstr),
                                                  op + str1 + '归约，GOTO[' + state[-1] + ',' + str(
                                                      process[0]) + ']=' + str(Table[int(state[-1])][inputstr[0]]) +
                                                  '状态' + str(Table[int(state[-1])][inputstr[0]]) + '入栈')
                        elif (self.judge(int(state[-1]))):
                            Project = ITER_SET[int(state[-1])]
                            for q in Project.grammar:
                                if (q.B == '$'):
                                    process.append(q.A)
                                    p = Table[int(state[-1])][q.A]
                                    state.append(p)
                                    count -= 1
                        else:
                            ProcessList[count] = (count, ''.join(state), ''.join(process), ''.join(inputstr), 'ERROR')
                            break
                    else:
                        ProcessList[count] = (count, ''.join(state), ''.join(process), ''.join(inputstr), 'ERROR')
                        break
                else:
                    ProcessList[count] = (count, ''.join(state), ''.join(process), ''.join(inputstr), 'ERROR')
                    break
            else:  # 如果不存在操作，就即在预测分析表中为空白，则报错，同时结束循环
                ProcessList[count] = (count, ''.join(state), ''.join(process), ''.join(inputstr), 'ERROR')
                break

        self.m_ListCtrl3.DeleteAllItems()  # 清除表中内容（不清除表头）
        for key, data in ProcessList.items():
            index = self.m_ListCtrl3.InsertItem(self.m_ListCtrl3.GetItemCount(), str(key))
            self.m_ListCtrl3.SetItem(index, 0, str(data[0]))
            self.m_ListCtrl3.SetItem(index, 1, data[1])
            self.m_ListCtrl3.SetItem(index, 2, data[2])
            self.m_ListCtrl3.SetItem(index, 3, data[3])
            self.m_ListCtrl3.SetItem(index, 4, data[4])
            self.m_ListCtrl3.SetColumnWidth(0, 40)
            self.m_ListCtrl3.SetColumnWidth(1, 90)
            self.m_ListCtrl3.SetColumnWidth(2, 90)
            self.m_ListCtrl3.SetColumnWidth(3, 110)
            self.m_ListCtrl3.SetColumnWidth(4, 1000)

    def m_button3OnButtonClick(self, event):
        # 清空内容
        FIRST.clear()
        LAN.clear()
        Table.clear()
        VT.clear()
        ProcessList.clear()
        self.m_ListCtrl1.DeleteAllItems()
        self.m_ListCtrl3.DeleteAllItems()
        self.m_ListCtrl4.DeleteAllItems()
        self.m_ListCtrl5.DeleteAllItems()
        self.m_ListCtrl6.DeleteAllItems()

        self.get_LAN()  # 得到文法
        self.get_first()  # 得到FIRST集
        self.get_VT()
        self.get_ITER_SET()
        self.get_ACTION()
        self.get_Table()
        self.analyze()  # 对输入字符串进行分析


if __name__ == '__main__':
    app = wx.App(False) #创建应用对象
    frame = MyFrame1(None)
    frame.Show(True)
    app.MainLoop()
