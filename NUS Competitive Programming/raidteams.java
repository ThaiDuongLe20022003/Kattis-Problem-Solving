import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class raidteams {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        Set<String> selected = new HashSet<>();
        List<Tuple> byFirst = new ArrayList<>();
        List<Tuple> bySecond = new ArrayList<>();
        List<Tuple> byThird = new ArrayList();

        int n = Integer.parseInt(br.readLine());

        Tuple[] mem = new Tuple[n];
        for (int i = 0; i < n; i++) {
            String[] input = br.readLine().split(" ");
            String name = input[0];
            int first = Integer.parseInt(input[1]);
            int second = Integer.parseInt(input[2]);
            int third = Integer.parseInt(input[3]);

            Tuple tuple = new Tuple(name, first, second, third);
            byFirst.add(tuple);
            bySecond.add(tuple);
            byThird.add(tuple);
            mem[i] = tuple;
        }

        Collections.sort(byFirst, new Comparator<Tuple>() {
            @Override
            public int compare(Tuple lhs, Tuple rhs) {
                if (lhs.first == rhs.first) {
                    return rhs.name.compareTo(lhs.name);
                }
                return Integer.compare(lhs.first, rhs.first);
            }
        });

        Collections.sort(bySecond, new Comparator<Tuple>() {
            @Override
            public int compare(Tuple lhs, Tuple rhs) {
                if (lhs.second == rhs.second) {
                    return rhs.name.compareTo(lhs.name);
                }
                return Integer.compare(lhs.second, rhs.second);
            }
        });

        Collections.sort(byThird, new Comparator<Tuple>() {
            @Override
            public int compare(Tuple lhs, Tuple rhs) {
                if (lhs.third == rhs.third) {
                    return rhs.name.compareTo(lhs.name);
                }
                return Integer.compare(lhs.third, rhs.third);
            }
        });

        while (true) {
            List<String> team = new ArrayList<>();

            while (!byFirst.isEmpty()) {
                Tuple player = byFirst.get(byFirst.size() - 1);
                byFirst.remove(byFirst.size() - 1);
                if (selected.contains(player.name)) continue;
                selected.add(player.name);
                team.add(player.name);
                break;
            }
            if (team.size() == 0) break;


            while (!bySecond.isEmpty()) {
                Tuple player = bySecond.get(bySecond.size() - 1);
                bySecond.remove(bySecond.size() - 1);
                if (selected.contains(player.name)) continue;
                selected.add(player.name);
                team.add(player.name);
                break;
            }
            if (team.size() == 1) break;


            while (!byThird.isEmpty()) {
                Tuple player = byThird.get(byThird.size() - 1);
                byThird.remove(byThird.size() - 1);
                if (selected.contains(player.name)) continue;
                selected.add(player.name);
                team.add(player.name);
                break;
            }
            if (team.size() == 2) break;

            Collections.sort(team);

            System.out.println(team.get(0) + " " + team.get(1) + " " + team.get(2));
        }
    }

    static class Tuple {
        String name;
        int first, second, third;

        Tuple(String name, int first, int second, int third) {
            this.name = name;
            this.first = first;
            this.second = second;
            this.third = third;
        }
    }
}