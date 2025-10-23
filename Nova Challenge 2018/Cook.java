package com.siqi.kattis;

import java.util.Scanner;

public class Cook {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int numberOfBoil = sc.nextInt();
        int[] startArray = new int[numberOfBoil];
        int[] endArray = new int[numberOfBoil];
        for (int i = 0; i < numberOfBoil; i++) {
            int startSecond = sc.nextInt();
            int endSecond = sc.nextInt();
            startArray[i] = startSecond;
            endArray[i] = endSecond;
        }
        int high=1000;
        int low=0;
        for (int l : startArray) {
            low= Math.max(low, l);
        }
        for (int h : endArray) {
            high= Math.min(high, h);
        }

        if (low>high) {
            System.out.println("edward is right");
            
        }else {
            System.out.println("gunilla has a point");
        }
        sc.close();
    }
}