#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
#define MAX 100
class Room {
public:
    Room* r[MAX];
    Room(int Number, string Type, string Whether, double Price){
        this->Number = Number;
        this->Type = Type;
        this->Whether = Whether;
        this->Price = Price;
    }
    void show() {
        cout << "房号：  " << Number << "\t" << "房间类型：  " << Type << "\t" << "房间状态:  " << Whether << "\t" << "价格:   " << Price << endl;
    }

    //目的：写入文件中
    int getNumber() {
        return Number;
    }
    string getWhether() {
        return Whether;
    }
    string getType() {
        return Type;
    }
    double getPrice() {
        return Price;
    }
    ~Room() {}
    void setWhether(string hhh) {
        this->Whether = hhh;
    }

private:
    int Now_RoomNum;
    int Number; //房号
    string Type;//类型
    string Whether;//是否有客人
    double Price;//价格
};
class Guest
{
public:
    Guest* g[MAX];	//客人对象指针数组
    Guest(string name, long long int Id, string sex, int number, int Intime, int days) //构造函数
    {
        this->name = name;
        this->Id = Id;
        this->sex = sex;
        this->number = number;
        this->Intime = Intime;
        this->days = days;
    }
    ~Guest() {}
    //目的：写入文件
    int getNumber() {
        return number;
    }
    string getName() {
        return name;
    }
    long long int getID() {
        return Id;
    }
    string getSex() {
        return sex;
    }
    int getIntime() {
        return Intime;
    }
    int getDays() {
        return days;
    }

    void show() {
        cout << "顾客姓名：  " << name << "\t 身份证号:  " << Id << "\t性别:  " << sex << "\t入住时间:  " << Intime << "\t入住天数:  " << days << endl;
    }
private:
    int Now_GuestNum;	//记录客人数量
    int number;//房号
    string name;//顾客姓名
    long long int Id;//身份证号
    string sex;//性别
    int Intime;//入住时间
    int days; //入住天数
};
class MENU {
public:
    Room* R[MAX];
    int Now_RoomNum;
    Guest* G[MAX];
    int Now_GuestNum;

    void InsertRoom(); //添加房间信息
    void Check_In();   //删除房间信息，登记入住
    void Check_Out();  //退房结账
    void Display_Info(int n);//展示房间或者客人信息
    void WriteRoom(Room* r);//保存房间到文件中
    void WriteGuest(Guest* g);//保存客人到文件中
    void Write_Info(int n);//写入之后进行保存到文件中
    void Read_Info();//读取文件中的信息

    void Search_Menu();//查询菜单
    void Search_EmpRoom();//查询空房间
    void Search_RoomNum();//按照房间号查询房间和客人信息
};
void MENU::Search_Menu() {
    int n;
    cout << "******************************************" << endl;
    cout << "******************查询界面****************" << endl;
    cout << "******************************************" << endl;
    cout << "****************1、查询空房间*************" << endl;
    cout << "***********2、查询客人和房间信息**********" << endl;
    cout << "******************************************" << endl;
    cout << endl << "请输入：";
    cin >> n;
    switch (n){
        case 1:
            Search_EmpRoom();
            break;
        case 2:
            Search_RoomNum();
            break;
    }
}
void MENU::Search_EmpRoom() {
    bool temp = 0;
    for (int i = 0; i < Now_RoomNum; i++) {
        if (R[i]->getWhether() == "无") {
            R[i]->show();
            temp = 1;
        }
    }
    if (temp != 1) {
        cout << "没有空房间，请另寻他处！" << endl;
    }
}
void MENU::Search_RoomNum() {
    int number;
    cout << "请输入要查询的房间号：";
    cin >> number;
    for (int i = 0; i < Now_RoomNum - 1; i++) {
        if (R[i]->getNumber() == number) {
            R[i]->show();
        }
    }
    for (int i = 0; i < Now_GuestNum - 1; i++) {
        if (G[i]->getNumber() == number) {
            G[i]->show();
        }
    }
}
void MENU::InsertRoom() {
    int Number;
    string Type;
    string Whether;
    double Price;
    cout << "请输入房号："; cin >> Number; cout << endl;
    cout << "请输入房间类型："; cin >> Type; cout << endl;
    cout << "请输入房间价格："; cin >> Price; cout << endl;
    cout << "请输入房间状态："; cin >> Whether; cout << endl;
    WriteRoom(new Room(Number, Type, Whether, Price));
}
void MENU::WriteRoom(Room* r) {
    ofstream ofs;
    ofs.open("room.txt", ios::app);
    ofs << r->getNumber() << " " << r->getType() << " " << r->getWhether() << " " << r->getPrice() << endl;
    ofs.close();
}
void MENU::WriteGuest(Guest* g) {
    ofstream ofs;
    ofs.open("guest.txt", ios::app);
    ofs << g->getName() << " " << g->getID() << " " << g->getSex() << " " << g->getNumber() << " " << g->getIntime() << " " << g->getDays() << endl;
    ofs.close();
}
void MENU::Write_Info(int n) {
    switch (n){
        case 1: {
            ofstream ofs;
            ofs.open("room.txt", ios::out);
            for (int i = 0; i < Now_RoomNum -1; i++) {
                WriteRoom(R[i]);
            }
            ofs.close();
            break;
        }
        case 2: {
            ofstream ofs;
            ofs.open("guest.txt", ios::out);
            for (int i = 0; i < Now_GuestNum-1&&(Now_GuestNum!=1); i++) {
                WriteGuest(G[i]);
            }
            ofs.close();
            break;
        }
        default:
            break;
    }
}
void MENU::Read_Info() {
    fstream GuestIn, RoomIn;
    RoomIn.open("room.txt", ios::in);
    if (!RoomIn) {
        cout << "请先创建room.txt文件" << endl;
        return;
    }
    int Now_RoomNum = 0;
    while (!RoomIn.eof()){
        int Number;
        string Type;
        string Whether;
        double Price;
        RoomIn >> Number >> Type >> Whether >> Price;
        //Room room(Number, Type, Whether, Price);
        R[Now_RoomNum] = new Room(Number, Type, Whether, Price);
        Now_RoomNum++;
    }
    this->Now_RoomNum = Now_RoomNum;
    RoomIn.close();

    GuestIn.open("guest.txt", ios::in);
    if (!GuestIn) {
        cout << "请先创建guest.txt文件" << endl;
        return;
    }
    int Now_GuestNum = 0;
    while (!GuestIn.eof()) {
        int number;//房号
        string name;//顾客姓名
        long long int Id;//身份证号
        string sex;//性别
        int Intime;//入住时间
        int days; //入住天数
        GuestIn >> name >> Id >> sex >> number >> Intime >> days;
        G[Now_GuestNum] = new Guest(name, Id, sex, number, Intime, days);
        Now_GuestNum++;
    }
    this->Now_GuestNum = Now_GuestNum;
    GuestIn.close();
}
void MENU::Check_In() {
    Read_Info();
    int number;//房号
    string name;//顾客姓名
    long long int Id;//身份证号
    string sex;//性别
    int Intime;//入住时间
    int days; //入住天数
    cout << "请输入房号："; cin >> number;
    cout << "请输入顾客姓名："; cin >> name;
    cout << "请输入顾客身份证号："; cin >> Id;
    cout << "请输入顾客性别："; cin >> sex;
    cout << "请输入顾客入住时间："; cin >> Intime;
    cout << "请输入入住天数："; cin >> days;
    for (int i = 0; i < Now_RoomNum - 1; i++) {
        if (number == R[i]->getNumber()) {
            R[i]->setWhether("有");
            Write_Info(1);
        }
    }
    WriteGuest(new Guest(name, Id, sex, number, Intime, days));
    cout << "顾客登记成功" << endl;
}
void MENU::Check_Out() {
    Read_Info();
    Display_Info(2);
    int num, temp = 0;
    cout << "请输入需要退房的房号："; cin >> num;
    for (int i = 0; i < Now_GuestNum; i++) {
        if (num == G[i]->getNumber()) {
            temp = i;
        }
    }
    for (int i = 0; i < Now_RoomNum- 1; i++) {
        if (G[temp]->getNumber() == R[i]->getNumber()) {
            R[i]->setWhether("无");
            cout << "退房成功，您消费了 " << G[temp]->getDays() * R[i]->getPrice() << " 元，欢迎下次光临！" << endl;
            Write_Info(1);
        }
    }
    for (int j = temp; j < Now_GuestNum && temp != 0; j++) {
        G[j] = G[j + 1];
    }
    this->Now_GuestNum--;
    Write_Info(2);
}
void MENU::Display_Info(int n)//浏览所有房间或者客户信息
{
    Read_Info();
    switch (n) {
        case 1:
            if (Now_RoomNum - 1 == 0) {
                cout << "还未录入房间，请抓紧干活" << endl;
                return;
            }
            for (int i = 0; i < Now_RoomNum - 1; i++){
                cout << "房号：" << R[i]->getNumber() << "\t房间类型: " << R[i]->getType() << "\t房间价格: " << R[i]->getPrice() << "\t房间状态: " << R[i]->getWhether() << endl << endl;
            }
            break;
        case 2:
            if (Now_GuestNum - 1 == 0) {
                cout << "还没有顾客入住，请抓紧拉客" << endl;
            }
            for (int i = 0; i < Now_GuestNum - 1; i++){
                cout << "房间号： " << G[i]->getNumber() << "\t顾客姓名: " << G[i]->getName() << "\t身份证号: " << G[i]->getID() << "\t顾客性别：" << G[i]->getSex() << "\t入住时间: " << G[i]->getIntime() << "\t入住天数: " << G[i]->getDays() << endl << endl;
            }
            break;
    }
}

void main_menu() {
    cout << "******************************************************************" << endl;
    cout << "*                         酒店房间管理系统                       *" << endl;
    cout << "*----------------------------------------------------------------*" << endl;
    cout << "*                        1、添加房间信息                         *" << endl;
    cout << "*                           2、登记入住                          *" << endl;
    cout << "*                           3、退房结账                          *" << endl;
    cout << "*                        4、显示房间信息                         *" << endl;
    cout << "*                        5、显示顾客信息                         *" << endl;
    cout << "*                         6、查询空房间                          *" << endl;
    cout << "*                      7、查询指定房间信息                       *" << endl;
    cout << "*                           8、退出系统                          *" << endl;
    cout << "******************************************************************" << endl;
}
int main() {
    MENU m;
    int n;
    while (1){
        system("cls");
        main_menu();
        cout << "请输入选项："; cin >> n;
        switch (n) {
            case 1:
                m.InsertRoom();
                system("pause");
                break;
            case 2:
                m.Check_In();
                system("pause");
                break;
            case 3:
                m.Check_Out();
                system("pause");
                break;
            case 4:
                m.Display_Info(1);
                system("pause");
                break;
            case 5:
                m.Display_Info(2);
                system("pause");
                break;
            case 6:
                m.Search_EmpRoom();
                system("pause");
                break;
            case 7:
                m.Search_RoomNum();
                system("pause");
                break;
            case 8:
                exit(0);
            default:
                cout << "输入选项错误，请重新输入" << endl;
        }
    }
    return 0;
}

