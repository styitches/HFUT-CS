package com.company;

public class changeTemperture {

    public static void main(String[] args) {
	    float sheshi = Float.parseFloat(args[0]);
        System.out.println("华氏温度：" + (sheshi * 1.75 + 32));
    }
}
