import java.util.*;

public class safepassage {
    static final int INF = Integer.MAX_VALUE;
    
    static class State implements Comparable<State> {
        int time, mask, cloak;
        
        State(int time, int mask, int cloak) {
            this.time = time;
            this.mask = mask;
            this.cloak = cloak;
        }
        
        @Override
        public int compareTo(State other) {
            return Integer.compare(this.time, other.time);
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[] times = new int[n];
        
        for (int i = 0; i < n; i++) {
            times[i] = scanner.nextInt();
        }
        
        int states = 1 << n;
        int[][] dp = new int[states][2];
        
        for (int i = 0; i < states; i++) {
            Arrays.fill(dp[i], INF);
        }
        
        // Initial state: everyone at gate, cloak at gate
        dp[0][0] = 0;
        
        PriorityQueue<State> pq = new PriorityQueue<>();
        pq.offer(new State(0, 0, 0));
        
        while (!pq.isEmpty()) {
            State current = pq.poll();
            int time = current.time;
            int mask = current.mask;
            int cloak = current.cloak;
            
            if (time > dp[mask][cloak]) {
                continue;
            }
            
            // Goal: everyone at dorm
            if (mask == (1 << n) - 1) {
                System.out.println(time);
                return;
            }
            
            if (cloak == 0) {
                // Cloak at gate: send people from gate to dorm
                
                // Send 1 person
                for (int i = 0; i < n; i++) {
                    if ((mask & (1 << i)) == 0) {
                        int newMask = mask | (1 << i);
                        int newTime = time + times[i];
                        if (newTime < dp[newMask][1]) {
                            dp[newMask][1] = newTime;
                            pq.offer(new State(newTime, newMask, 1));
                        }
                    }
                }
                
                // Send 2 people
                for (int i = 0; i < n; i++) {
                    if ((mask & (1 << i)) == 0) {
                        for (int j = i + 1; j < n; j++) {
                            if ((mask & (1 << j)) == 0) {
                                int newMask = mask | (1 << i) | (1 << j);
                                int newTime = time + Math.max(times[i], times[j]);
                                if (newTime < dp[newMask][1]) {
                                    dp[newMask][1] = newTime;
                                    pq.offer(new State(newTime, newMask, 1));
                                }
                            }
                        }
                    }
                }
            } else {
                // Cloak at dorm: send people from dorm to gate
                
                // Send 1 person back
                for (int i = 0; i < n; i++) {
                    if ((mask & (1 << i)) != 0) {
                        int newMask = mask ^ (1 << i);
                        int newTime = time + times[i];
                        if (newTime < dp[newMask][0]) {
                            dp[newMask][0] = newTime;
                            pq.offer(new State(newTime, newMask, 0));
                        }
                    }
                }
                
                // Send 2 people back
                for (int i = 0; i < n; i++) {
                    if ((mask & (1 << i)) != 0) {
                        for (int j = i + 1; j < n; j++) {
                            if ((mask & (1 << j)) != 0) {
                                int newMask = mask ^ (1 << i) ^ (1 << j);
                                int newTime = time + Math.max(times[i], times[j]);
                                if (newTime < dp[newMask][0]) {
                                    dp[newMask][0] = newTime;
                                    pq.offer(new State(newTime, newMask, 0));
                                }
                            }
                        }
                    }
                }
            }
        }
        
        scanner.close();
    }
}