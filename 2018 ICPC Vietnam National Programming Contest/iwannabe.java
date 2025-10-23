import java.io.*;
import java.util.*;

public class iwannabe {
    public static void main(String[] args) throws Exception {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter dc = new BufferedWriter(new OutputStreamWriter(System.out));

        String[] tokens = sc.readLine().split(" ");
        int cases = Integer.parseInt(tokens[0]);
        int k = Integer.parseInt(tokens[1]);
        Pokemon[] attack = new Pokemon[cases];
        Pokemon[] defense = new Pokemon[cases];
        Pokemon[] health = new Pokemon[cases];
        for (int x = 0; x < cases; x++)
            attack[x] = defense[x] = health[x] = new Pokemon(sc.readLine().split(" "));
        Arrays.sort(attack, new AtkCompare());
        Arrays.sort(defense, new DefCompare());
        Arrays.sort(health, new HealthCompare());
        int count = 0;
        for (int x = 0; x < k; x++) {
            if (!attack[x].taken) {
                attack[x].taken = true;
                count++;
            }
            if (!defense[x].taken) {
                defense[x].taken = true;
                count++;
            }
            if (!health[x].taken) {
                health[x].taken = true;
                count++;
            }
        }
        dc.write(count + "\n");

        dc.close();
        sc.close();
    }
}

class Pokemon {
    public long a, d, h;
    public boolean taken;

    public Pokemon(String[] stats) {
        this.a = Long.parseLong(stats[0]);
        this.d = Long.parseLong(stats[1]);
        this.h = Long.parseLong(stats[2]);
        taken = false;
    }
}

class AtkCompare implements Comparator<Pokemon> {
    @Override
    public int compare(Pokemon a, Pokemon b) {
        return Long.compare(b.a, a.a); // Changed the comparison to use Long.compare
    }
}

class DefCompare implements Comparator<Pokemon> {
    @Override
    public int compare(Pokemon a, Pokemon b) {
        return Long.compare(b.d, a.d); // Changed the comparison to use Long.compare
    }
}

class HealthCompare implements Comparator<Pokemon> {
    @Override
    public int compare(Pokemon a, Pokemon b) {
        return Long.compare(b.h, a.h); // Changed the comparison to use Long.compare
    }
}