#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long a, d, h;
} Poke;

int cmpa(const void* a, const void* b) {
    Poke* p1 = (Poke*)a;
    Poke* p2 = (Poke*)b;
    if (p1->a > p2->a) return -1;
    if (p1->a < p2->a) return 1;
    return 0;
}

int cmpd(const void* a, const void* b) {
    Poke* p1 = (Poke*)a;
    Poke* p2 = (Poke*)b;
    if (p1->d > p2->d) return -1;
    if (p1->d < p2->d) return 1;
    return 0;
}

int cmph(const void* a, const void* b) {
    Poke* p1 = (Poke*)a;
    Poke* p2 = (Poke*)b;
    if (p1->h > p2->h) return -1;
    if (p1->h < p2->h) return 1;
    return 0;
}

int comparePoke(const void* a, const void* b) {
    Poke* p1 = (Poke*)a;
    Poke* p2 = (Poke*)b;
    if (p1->a != p2->a) return (p1->a > p2->a) ? 1 : -1;
    if (p1->d != p2->d) return (p1->d > p2->d) ? 1 : -1;
    if (p1->h != p2->h) return (p1->h > p2->h) ? 1 : -1;
    return 0;
}

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    
    Poke* v = malloc(n * sizeof(Poke));
    for (long long i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &v[i].a, &v[i].d, &v[i].h);
    }
    
    Poke* all = malloc(n * 3 * sizeof(Poke));
    long long all_size = 0;
    
    qsort(v, n, sizeof(Poke), cmpa);
    for (long long i = 0; i < m && i < n; i++) {
        all[all_size++] = v[i];
    }
    
    qsort(v, n, sizeof(Poke), cmpd);
    for (long long i = 0; i < m && i < n; i++) {
        all[all_size++] = v[i];
    }
    
    qsort(v, n, sizeof(Poke), cmph);
    for (long long i = 0; i < m && i < n; i++) {
        all[all_size++] = v[i];
    }
    
    qsort(all, all_size, sizeof(Poke), comparePoke);
    
    long long unique_count = 0;
    if (all_size > 0) {
        unique_count = 1;
        for (long long i = 1; i < all_size; i++) {
            if (all[i].a != all[i-1].a || all[i].d != all[i-1].d || all[i].h != all[i-1].h) {
                unique_count++;
            }
        }
    }
    
    printf("%lld\n", unique_count);
    
    free(v);
    free(all);
    return 0;
}