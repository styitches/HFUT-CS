package com;

import java.util.*;;

class Person{
    public String ID;
    public String Name;
    public String e_mail;
    public String toString(){
        return this.ID + "; " + this.Name + "; ";
    }
}
class Student extends Person{
    String classState;
    @Override
    public String toString(){
        return "Student" + "; " + super.toString();
    }

    public Student(){
        System.out.println("请输入学生的信息：");
        Scanner scan1 = new Scanner(System.in);
        System.out.println("ID:");
        ID = scan1.nextLine();
        System.out.println("Name:");
        Name = scan1.nextLine();
        System.out.println("e_mail:");
        e_mail = scan1.nextLine();
        System.out.println("calssState:");
        classState = scan1.nextLine();
    }
}
class Employee extends Person{}
class Faculty extends Employee{
    String majorCourse;
    String majorInfo;

    @Override
    public String toString() {
        return "Faculty"+ "; " + super.toString();
    }

    public Faculty(){
        System.out.println("请输入教师的信息：");
        Scanner scan1 = new Scanner(System.in);
        System.out.println("ID:");
        ID = scan1.nextLine();
        System.out.println("Name:");
        Name = scan1.nextLine();
        System.out.println("e_mail:");
        e_mail = scan1.nextLine();
        System.out.println("majorInfo:");
        majorInfo = scan1.nextLine();
        System.out.println("majorCourse:");
        majorCourse = scan1.nextLine();
    }
}
class Staff extends Employee{
    String officeInfo;

    @Override
    public String toString() {
        return "Staff" + "; " + super.toString();
    }

    public Staff(){
        System.out.println("请输入职员的信息：");
        Scanner scan1 = new Scanner(System.in);
        System.out.println("ID:");
        ID = scan1.nextLine();
        System.out.println("Name:");
        Name = scan1.nextLine();
        System.out.println("e_mail:");
        e_mail = scan1.nextLine();
        System.out.println("officeInfo:");
        officeInfo = scan1.nextLine();
    }
}
public class woke2_2 {
    public static void main(String[] args) {
        Person[] objectArray = new Person[5];
        for (int i = 0; i < 5; i++){
            Random randNum = new Random();
            int x = randNum.nextInt(3) + 1;
            switch (x){
                case 1:
                    objectArray[i] = new Student();
                    break;
                case 2:
                    objectArray[i] = new Faculty();
                    break;
                case 3:
                    objectArray[i] = new Staff();
                    break;
            }
        }

        for (int i = 0; i < 5; i++){
            System.out.println(objectArray[i].toString());
        }
    }
}
