import random
import random as r

xin = ['杨', '张', '陈', '安', '金', '姜']

min1 = ['家', '虎', '龙', '雨', '彤', '玲']

min2 = ['', '雨', '骏', '', '国', '']


class Student():
    # 姓名
    Name = '人'
    # 学号
    Numbers = "200300"
    # 性别
    Gender = '男'
    # 班级
    Classes = 1
    # 成绩
    Achievement = {'高数': 0, '英语': 0, '计算机': 0}

    def __init__(self, name, numbers, gender, classes, achievement):
        self.Name = name
        self.Numbers = numbers
        self.Gender = gender
        self.Classes = classes
        self.Achievement = achievement


class Class():
    list = []

    def __init__(self, n):
        for i in range(n):
            name = r.choice(xin) + r.choice(min1) + r.choice(min2)
            numbers = '2020' + str(random.randint(10, 99))
            Gender = self.gender(random.randint(1, 3))
            Math = random.randint(1, 101)
            English = random.randint(1, 101)
            Computer = random.randint(1, 101)
            achievement = {'高数': Math, '英语': English, '计算机': Computer}
            student = Student(name, numbers, Gender, 1, achievement)
            self.list.append(student)
        self.creat()
        self.sort_achievement()

    def gender(self, x):
        if x == 1:
            return "男"
        else:
            return "女"

    def creat(self):
        with open('Class_list.txt', "w+") as f:
            for i in self.list:
                str1 = i.Numbers + " " + i.Name + " " + i.Gender + " " + "高数：" + str(
                    i.Achievement["高数"]) + " " + "英语：" + str(i.Achievement["英语"]) + " " + "计算机：" + str(
                    i.Achievement["计算机"])
                f.write(str1+"\n")

    def sort_achievement(self):
        data = []

        def find(list):
            average = list[6]
            return average

        for line in open("Class_list.txt", 'r'):
            data1 = line.rsplit()
            Math = data1[3].split("：")
            Gender = {'Math':Math[1]}
            English = data1[4].split("：")
            Gender['English'] = English[1]
            Computer = data1[5].split("：")
            Gender['Computer'] = Computer[1]
            average = (int(Gender["Math"]) + int(Gender["English"]) + int(Gender["Computer"])) / 3
            data2 = [data1[0], data1[1], data1[2], Gender["Math"], Gender["English"], Gender["Computer"], average]
            data.append(data2)
        data.sort(key=lambda x: find(x))
        for i in data:
            print(i)


classs = Class(10)
