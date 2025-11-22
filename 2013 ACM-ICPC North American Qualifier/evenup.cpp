#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int value;
    Node* next;
};

class MemStack {
private:
    vector<Node> memory;
    size_t current;
public:
    void init(int max_cap) {
        memory.resize(max_cap);
        current = 0;
    }
    
    Node* allocate(int value) {
        memory[current].value = value;
        memory[current].next = nullptr;
        return &memory[current++];
    }
};

class List {
public:
    int count;
    Node* head;
    Node* tail;
    
    void init() {
        count = 0;
        head = nullptr;
        tail = nullptr;
    }
    
    void push_back(MemStack& mem, int value) {
        if (head == nullptr) {
            head = mem.allocate(value);
            tail = head;
        } else {
            tail->next = mem.allocate(value);
            tail = tail->next;
        }
        count++;
    }
};

int rem(MemStack& m, List& l) {
    int total_removed = 0;
    
    // Remove from head
    while (l.count > 1 && (l.head->value & 1) == (l.head->next->value & 1)) {
        l.head = l.head->next->next;
        l.count -= 2;
        total_removed += 2;
    }
    
    // Remove from middle
    if (l.count >= 3) {
        Node* prev = l.head;
        Node* curr = l.head->next;
        Node* next = l.head->next->next;
        
        while (l.count > 1 && next != nullptr) {
            if ((curr->value & 1) == (next->value & 1)) {
                l.count -= 2;
                total_removed += 2;
                prev->next = next->next;
                curr = prev->next;
                if (curr == nullptr) break;
                next = curr->next;
            } else {
                prev = curr;
                curr = next;
                next = next->next;
            }
        }
    }
    
    return total_removed;
}

int main() {
    MemStack m;
    List l;
    int n;
    cin >> n;
    
    m.init(n);
    l.init();
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        l.push_back(m, x);
    }
    
    int removes = 0, remove_count = 0;
    while (l.count > 1 && (remove_count = rem(m, l))) {
        removes += remove_count;
    }
    
    cout << n - removes << endl;
    return 0;
}