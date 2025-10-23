import java.util.HashMap;
import java.util.Iterator;
import java.util.Scanner;
import java.util.TreeMap;

public class terracehill {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int count = in.nextInt();

        TreeMap<Integer, Integer> heights = new TreeMap<>();
        int prevHeight = Integer.MAX_VALUE;
        long result = 0;
        for (int i = 0; i < count; i++) {
            int height = in.nextInt();
            if (height > prevHeight) {
                Iterator<Integer> it = heights.keySet().iterator();
                while(it.hasNext()) {
                    Integer val = it.next();
                    if(val == height) result += i - heights.get(val) - 1;
                    if(val <= height) it.remove();
                    else break;
                }
            }

            heights.put(height, i);
            prevHeight = height;
        }

        System.out.println(result);
    }
}