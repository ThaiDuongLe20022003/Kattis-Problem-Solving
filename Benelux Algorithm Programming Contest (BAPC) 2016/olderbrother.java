/** * OOP Java Project  WiSe 2023/2024

* Problem: Older Brother

* Link: https://open.kattis.com/contests/xreb4q/problems/olderbrother ;

* @author Nguyen Hoang Huan 

* @version 1.0, 25.10.2023

* Method : number theory, arraylists

* Status : Accepted 

* Runtime: 0.14 */

import java.util.*;

public class olderbrother {

    private List<Integer> primes = new ArrayList<>();

    public static void main(String[] args) {
        new olderbrother().run();
    }

    private void run() {
        try (Scanner sc = new Scanner(System.in)) {
            int q = sc.nextInt();
            for (int i = 2; i < Math.sqrt(q) + 2; i++) {
                if (isPrime(i)) {
                    primes.add(i);
                    if (ok(i, q)) {
                        System.out.println("yes");
                        return;
                    }
                }
            }
            System.out.println(isPrime(q) ? "yes" : "no");
        }
    }

    private boolean ok(int prime, int q) {
        if (q < prime) {
            return false;
        }
        while (q % prime == 0) {
            q /= prime;
        }
        return q == 1;
    }

    private boolean isPrime(int i) {
        if (i < 2) {
            return false;
        }
        for (int p : primes) {
            if (i == p) {
                return true;
            }
            if (i % p == 0) {
                return false;
            }
        }
        return true;
    }
}