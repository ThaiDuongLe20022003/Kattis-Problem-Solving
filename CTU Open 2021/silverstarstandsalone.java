import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class silverstarstandsalone {
    public static HashMap<Integer, List<Integer>> nextSteps = new HashMap<Integer, List<Integer>>();

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int max = sc.nextInt();
        int[] primes = new int[]{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211};

        int i = 0;
        while(primes[i] < max) {
            int j = 1;
            List<Integer> list =  new LinkedList<>();
            while(i+j < primes.length && primes[i+j] <= max && (primes[i+j] - primes[i]) <= 14) {
                list.add(primes[i+j]);
                j++;
            }
            nextSteps.put(primes[i], list);
            i++;
        }

        HashMap<Integer, Long> stepCount = new HashMap<>();
        stepCount.put(2, 1l);
        i = 0;
        while(primes[i] < max) {
            Integer current = primes[i];
            for(Integer next : nextSteps.get(primes[i])) {
                stepCount.putIfAbsent(next, 0l);
                Long n = stepCount.get(next) + stepCount.get(current);
                stepCount.put(next, n);
            }
            i++;
        }

        System.out.println(stepCount.get(max));
    }
}