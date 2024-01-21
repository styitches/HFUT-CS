package com.company;

public class greek {
    public static void main(String[] args) {
        char a = 'α', b, c = 'ω';
        System.out.println("希腊字母表：");
        for(int i = (int)a; i <= (int)c; i++){
            b = (char)i;
            System.out.print(" " + b);
        }
    }
}
