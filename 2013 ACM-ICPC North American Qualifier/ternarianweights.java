import java.util.*;
import java.io.*;

public class ternarianweights {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        boolean firstCase = true;
        
        while (n-- > 0) {
            if (!firstCase) {
                System.out.println();
            }
            firstCase = false;
            
            long x = scanner.nextLong();
            
            List<Long> leftWeights = new ArrayList<>();
            List<Long> rightWeights = new ArrayList<>();
            long currentPowerOf3 = 1;
            
            while (x > 0) {
                int rem = (int)(x % 3);
                if (rem == 1) {
                    rightWeights.add(currentPowerOf3);
                    x -= 1;
                } else if (rem == 2) {
                    leftWeights.add(currentPowerOf3);
                    x += 1;
                }
                
                x /= 3;
                if (x > 0) {
                    if (currentPowerOf3 > Long.MAX_VALUE / 3) {
                        break;
                    }
                    currentPowerOf3 *= 3;
                }
            }
            
            // Sort in descending order
            Collections.sort(leftWeights, Collections.reverseOrder());
            Collections.sort(rightWeights, Collections.reverseOrder());
            
            // Print results
            System.out.print("left pan:");
            for (long weight : leftWeights) {
                System.out.print(" " + weight);
            }
            System.out.println();
            
            System.out.print("right pan:");
            for (long weight : rightWeights) {
                System.out.print(" " + weight);
            }
            System.out.println();
        }
        
        scanner.close();
    }
}