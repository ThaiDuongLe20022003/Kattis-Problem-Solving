import java.util.*;

class Poke implements Comparable<Poke> {
    long a, d, h;
    
    Poke(long a, long d, long h) {
        this.a = a;
        this.d = d;
        this.h = h;
    }
    
    @Override
    public int compareTo(Poke other) {
        if (this.a != other.a) return Long.compare(this.a, other.a);
        if (this.d != other.d) return Long.compare(this.d, other.d);
        return Long.compare(this.h, other.h);
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Poke poke = (Poke) obj;
        return a == poke.a && d == poke.d && h == poke.h;
    }
    
    @Override
    public int hashCode() {
        return Objects.hash(a, d, h);
    }
}

public class iwannabe {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextLong();
        long m = scanner.nextLong();
        
        List<Poke> v = new ArrayList<>();
        for (long i = 0; i < n; i++) {
            long a = scanner.nextLong();
            long d = scanner.nextLong();
            long h = scanner.nextLong();
            v.add(new Poke(a, d, h));
        }
        
        Set<Poke> all = new TreeSet<>();
        
        v.sort((p1, p2) -> Long.compare(p2.a, p1.a));
        for (long i = 0; i < m && i < v.size(); i++) {
            all.add(v.get((int)i));
        }
        
        v.sort((p1, p2) -> Long.compare(p2.d, p1.d));
        for (long i = 0; i < m && i < v.size(); i++) {
            all.add(v.get((int)i));
        }
        
        v.sort((p1, p2) -> Long.compare(p2.h, p1.h));
        for (long i = 0; i < m && i < v.size(); i++) {
            all.add(v.get((int)i));
        }
        
        System.out.println(all.size());
    }
}