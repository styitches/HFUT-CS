"""
图书管理系统
"""
import time

# books={书名:剩余数量}
books = {"数据结构": 5, "离散数学": 3, "概率论": 1,"Python":0}
# students_books=[name,{书}]
students_books = {"杨程锦": []}



if __name__ == "__main__":
    print("*" * 50)
    print("欢迎来到辣个男人的图书馆".center(50))
    print("*" * 50)
    while True:
        choices = input("""             请选择你所需要的功能
1.查询书籍 2.借书 3.还书 4.显示所有书籍 5.查询用户所借的书  6.退出系统:""")
        if choices == '1':
            # 查询书籍
            print('--------查询书籍---------')
            search_book = input('请输入要查询的书籍名称:')
            # 遍历books
            for book in books.keys():
                if search_book in book:
                    print("正在查找,请稍等")
                    time.sleep(1)
                    if books[search_book] > 0:
                        print("你说查找的书,目前还有{}本".format(books[search_book]))
                        break
                    else:
                        print("你所查找的书,已经借完,请过段时间之后再来")
                        break
            else:
                print("对不起你所输入的书不存在,我们将在今后补充！")

        elif choices == '2':
            # 借书
            print("欢迎来到借书页面".center(50))
            flag = True
            while flag:
                user_name = input("请输入用户名")
                borrow_book = input("请输入你所借的书名")
                for book in books.keys():
                    if borrow_book == book:
                        if user_name in students_books.keys():
                            if books[borrow_book] > 0:
                                if borrow_book not in students_books[user_name]:
                                    print(r"你已经借书<<{}>>".format(borrow_book))
                                    students_books[user_name].append(borrow_book)
                                    books[borrow_book] -= 1
                                    print(r"现在<<{}>>,剩余{}本".format(borrow_book, books[borrow_book]))
                                    flag = False
                                    break
                                else:
                                    print("对不起,你已经借了一本")
                                    flag = False
                                    break
                            else:
                                print("对不起你所借的书剩余{}本,请下次再来".format(books[borrow_book]))
                                flag = False
                                break
                        else:
                            students_books[user_name] = []
                            students_books[user_name].append(borrow_book)
                            books[borrow_book] -= 1
                            print(r"新用户( {} )已经借书<< {} >>,目前此书剩余{}本".format(user_name, borrow_book, books[borrow_book]))
                            flag = False
                            break

                else:
                    print("对不起,你所查找的书不存在,在今后我们将会更新！")

        elif choices == '3':
            flag = True
            while flag:
                user_name = input("请输入你的名字")
                repay_book = input("请输入你所要还的书")
                for name in students_books.keys():
                    # 先去判断有没有这个人
                    if name == user_name:
                        # 判断有没有这本书在不在该用户
                        if repay_book in students_books[name]:
                            # 判断此本书书否在图书馆库里面
                            if repay_book in books.keys():
                                books[repay_book] += 1
                                students_books[name].remove(repay_book)
                                print("正在还书,请稍等")
                                time.sleep(1)
                                print("你已经还书了,这本书数量为{}".format(books[repay_book]))
                                flag = False
                                break
                            else:
                                print("此本书不在图书馆库里面,请重新输入")
                                break
                        else:
                            print("你所输入的书,并在你的借书目录里面,请重新输入")
                            break
                else:
                    print("对不起你所输入的人不存在,请重新输入")

        elif choices == '4':
            # 显示所有书籍
            print("图书馆目前所藏书籍如下:")
            for bookkey, bookvalue in list(books.items()):
                print(r"<<{}>>目前还有 {} 本".format(bookkey, bookvalue))
                time.sleep(0.5)

        elif choices == '5':
            username = input(" 请输入你要查询的用户名")
            for stu in students_books.keys():
                if username == stu:
                    print("{}所借的书有{}".format(user_name, students_books[username]))
                else:
                    print("你查找的用户不在")

        elif choices == '6':
            choice = input("确定是否退出,确认请输入yes,否则请输入no:\n")
            if choice == 'yes':
                print("感谢你的使用,再见")
                break
            if choice == 'no':
                print("帮到你很开心")
            else:
                print('输入错误请重新输入....')

