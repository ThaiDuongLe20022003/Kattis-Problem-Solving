import java.util.*;
import java.io.*;

public class torn2pieces {
    static List<String> split(String s) {
        return Arrays.asList(s.split(" "));
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = Integer.parseInt(scanner.nextLine());
        Map<String, Set<String>> adj = new HashMap<>();

        for (int i = 0; i < n; i++) {
            String s = scanner.nextLine();
            List<String> v = split(s);
            
            for (int j = 1; j < v.size(); j++) {
                adj.putIfAbsent(v.get(0), new HashSet<>());
                adj.putIfAbsent(v.get(j), new HashSet<>());
                
                adj.get(v.get(0)).add(v.get(j));
                adj.get(v.get(j)).add(v.get(0));
            }
        }

        String start = scanner.next();
        String end = scanner.next();

        Map<String, String> prev = new HashMap<>();
        prev.put(start, "thisisthestart");

        Queue<String> q = new LinkedList<>();
        q.add(start);
        
        while (!q.isEmpty()) {
            String curr = q.poll();

            if (adj.containsKey(curr)) {
                for (String next : adj.get(curr)) {
                    if (!prev.containsKey(next)) {
                        prev.put(next, curr);
                        q.add(next);
                    }
                }
            }
        }

        if (!prev.containsKey(end)) {
            System.out.println("no route found");
            return;
        }

        List<String> ans = new ArrayList<>();
        String current = end;
        while (!current.equals("thisisthestart")) {
            ans.add(current);
            current = prev.get(current);
        }
        Collections.reverse(ans);

        System.out.println(String.join(" ", ans));
        
        scanner.close();
    }
}