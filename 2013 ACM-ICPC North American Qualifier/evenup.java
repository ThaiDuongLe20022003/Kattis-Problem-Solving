import java.util.Scanner;

class Node {
    int value;
    Node next;
}

class MemStack {
    private Node[] memory;
    private int current;
    
    public void init(int max_cap) {
        memory = new Node[max_cap];
        for (int i = 0; i < max_cap; i++) {
            memory[i] = new Node();
        }
        current = 0;
    }
    
    public Node allocate(int value) {
        memory[current].value = value;
        memory[current].next = null;
        return memory[current++];
    }
}

class List {
    int count;
    Node head;
    Node tail;
    
    public void init() {
        count = 0;
        head = null;
        tail = null;
    }
    
    public void pushBack(MemStack mem, int value) {
        if (head == null) {
            head = mem.allocate(value);
            tail = head;
        } else {
            tail.next = mem.allocate(value);
            tail = tail.next;
        }
        count++;
    }
}

public class evenup {
    static int rem(MemStack m, List l) {
        int total_removed = 0;
        
        // Remove from head
        while (l.count > 1 && (l.head.value & 1) == (l.head.next.value & 1)) {
            l.head = l.head.next.next;
            l.count -= 2;
            total_removed += 2;
        }
        
        // Remove from middle
        if (l.count >= 3) {
            Node prev = l.head;
            Node curr = l.head.next;
            Node next = l.head.next.next;
            
            while (l.count > 1 && next != null) {
                if ((curr.value & 1) == (next.value & 1)) {
                    l.count -= 2;
                    total_removed += 2;
                    prev.next = next.next;
                    curr = prev.next;
                    if (curr == null) break;
                    next = curr.next;
                } else {
                    prev = curr;
                    curr = next;
                    next = next.next;
                }
            }
        }
        
        return total_removed;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        MemStack m = new MemStack();
        List l = new List();
        int n = scanner.nextInt();
        
        m.init(n);
        l.init();
        
        for (int i = 0; i < n; i++) {
            int x = scanner.nextInt();
            l.pushBack(m, x);
        }
        
        int removes = 0, remove_count = 0;
        while (l.count > 1 && (remove_count = rem(m, l)) > 0) {
            removes += remove_count;
        }
        
        System.out.println(n - removes);
        scanner.close();
    }
}