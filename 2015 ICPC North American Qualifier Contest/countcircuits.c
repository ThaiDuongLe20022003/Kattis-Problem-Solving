#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct Node {
    Pair key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node** buckets;
    int size;
} HashMap;

HashMap* createHashMap(int size) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->size = size;
    map->buckets = (Node**)calloc(size, sizeof(Node*));
    return map;
}

unsigned int hash(Pair p, int size) {
    return (unsigned int)(p.first * 31 + p.second) % size;
}

void put(HashMap* map, Pair key, int value) {
    unsigned int index = hash(key, map->size);
    Node* current = map->buckets[index];
    
    while (current != NULL) {
        if (current->key.first == key.first && current->key.second == key.second) {
            current->value += value;
            return;
        }
        current = current->next;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = map->buckets[index];
    map->buckets[index] = newNode;
}

int get(HashMap* map, Pair key) {
    unsigned int index = hash(key, map->size);
    Node* current = map->buckets[index];
    
    while (current != NULL) {
        if (current->key.first == key.first && current->key.second == key.second) {
            return current->value;
        }
        current = current->next;
    }
    return 0;
}

void generate(Pair* v, int v_size, HashMap* map) {
    for (int i = 1; i < (1 << v_size); i++) {
        Pair sum = {0, 0};
        for (int j = 0; j < v_size; j++) {
            if ((1 << j) & i) {
                sum.first += v[j].first;
                sum.second += v[j].second;
            }
        }
        put(map, sum, 1);
    }
}

void freeHashMap(HashMap* map) {
    for (int i = 0; i < map->size; i++) {
        Node* current = map->buckets[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(map->buckets);
    free(map);
}

int main() {
    int n;
    scanf("%d", &n);
    
    Pair* v1 = (Pair*)malloc(n * sizeof(Pair));
    Pair* v2 = (Pair*)malloc(n * sizeof(Pair));
    int v1_size = 0, v2_size = 0;
    
    for (int i = 0; i < n; i++) {
        Pair p;
        scanf("%d %d", &p.first, &p.second);
        if (i % 2 == 0) {
            v1[v1_size++] = p;
        } else {
            v2[v2_size++] = p;
        }
    }
    
    HashMap* set1 = createHashMap(100000);
    HashMap* set2 = createHashMap(100000);
    
    generate(v1, v1_size, set1);
    generate(v2, v2_size, set2);
    
    long long ans = 0;
    
    // Iterate through all keys in set1
    for (int i = 0; i < set1->size; i++) {
        Node* current = set1->buckets[i];
        while (current != NULL) {
            Pair p = current->key;
            Pair target = {-p.first, -p.second};
            ans += current->value * get(set2, target);
            current = current->next;
        }
    }
    
    // Add empty subsets
    Pair zero = {0, 0};
    ans += get(set1, zero);
    ans += get(set2, zero);
    
    printf("%lld\n", ans);
    
    free(v1);
    free(v2);
    freeHashMap(set1);
    freeHashMap(set2);
    
    return 0;
}