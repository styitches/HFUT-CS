package com;
public class work2_5 {
    public static void main(String[] args) {
        try {
            Integer.parseInt(args[0]);
        } catch (NumberFormatException e){
            System.out.println("数字格式错误");
        }
    }
}
