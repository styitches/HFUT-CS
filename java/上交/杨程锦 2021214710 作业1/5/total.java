package com.company;

import java.math.BigInteger;

public class total {
    public static void main(String[] args) {
        BigInteger x = new BigInteger("1");
        BigInteger y = new BigInteger("0");
        int i = 1;
        int j = 1;
        do {
            x = x.multiply(BigInteger.valueOf(j));
            j++;
            y = y.add(x);
            i++;
        } while (i <= 100);
        System.out.println(y);
    }
}
