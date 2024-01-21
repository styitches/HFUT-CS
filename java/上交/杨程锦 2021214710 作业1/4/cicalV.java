package com.company;

public class cicalV {
    public static void main(String[] args) {
        double pai = Math.PI;
        double r = Double.parseDouble(args[0]);
        System.out.println("圆球的体积：" + ((4/3) * pai * r * r * r));
    }
}
