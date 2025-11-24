import java.util.*;
import java.io.*;

public class canofworms {
    static class Fence implements Comparable<Fence> {
        int pos, strength, idx;
        
        Fence(int pos, int strength, int idx) {
            this.pos = pos;
            this.strength = strength;
            this.idx = idx;
        }
        
        @Override
        public int compareTo(Fence other) {
            return Integer.compare(this.pos, other.pos);
        }
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        
        Fence[] fences = new Fence[n];
        int[] l = new int[n];
        int[] r = new int[n];
        
        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int pos = Integer.parseInt(st.nextToken());
            int strength = Integer.parseInt(st.nextToken());
            fences[i] = new Fence(pos, strength, i);
            l[i] = i;
            r[i] = i;
        }
        
        Arrays.sort(fences);
        
        boolean change;
        do {
            change = false;
            
            // Forward pass
            Stack<Integer> stack = new Stack<>();
            for (int i = 0; i < n; i++) {
                while (!stack.isEmpty() && 
                       Math.abs(fences[i].pos - fences[stack.peek()].pos) <= fences[i].strength) {
                    int j = stack.pop();
                    
                    if (l[i] > l[j]) {
                        l[i] = l[j];
                        change = true;
                    }
                    if (r[i] < r[j]) {
                        r[i] = r[j];
                        change = true;
                    }
                }
                stack.push(i);
            }
            
            // Backward pass
            stack = new Stack<>();
            for (int i = n - 1; i >= 0; i--) {
                while (!stack.isEmpty() && 
                       Math.abs(fences[i].pos - fences[stack.peek()].pos) <= fences[i].strength) {
                    int j = stack.pop();
                    
                    if (l[i] > l[j]) {
                        l[i] = l[j];
                        change = true;
                    }
                    if (r[i] < r[j]) {
                        r[i] = r[j];
                        change = true;
                    }
                }
                stack.push(i);
            }
            
        } while (change);
        
        int[] cans = new int[n];
        for (int i = 0; i < n; i++) {
            cans[fences[i].idx] = r[i] - l[i] + 1;
        }
        
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; i++) {
            sb.append(cans[i]).append(" ");
        }
        System.out.println(sb.toString().trim());
    }
}