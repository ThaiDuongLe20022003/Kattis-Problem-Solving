#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
    long long x, y;
} Point;

Point point(long long x, long long y) {
    Point p = {x, y};
    return p;
}

long long cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int compare_points(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x) return (p1->x > p2->x) ? 1 : -1;
    return (p1->y > p2->y) ? 1 : -1;
}

void remove_duplicates(Point *points, int *size) {
    if (*size == 0) return;
    
    int j = 0;
    for (int i = 1; i < *size; i++) {
        if (points[i].x != points[j].x || points[i].y != points[j].y) {
            j++;
            points[j] = points[i];
        }
    }
    *size = j + 1;
}

int monotone_chain(Point *points, int n, Point *hull, bool collinear) {
    if (n < 3) {
        for (int i = 0; i < n; i++) hull[i] = points[i];
        return n;
    }
    
    qsort(points, n, sizeof(Point), compare_points);
    remove_duplicates(points, &n);
    
    int hull_size = 0;
    
    for (int i = 0; i < n; i++) {
        while (hull_size > 1) {
            long long cp = cross(hull[hull_size-2], hull[hull_size-1], points[i]);
            if (collinear ? cp <= 0 : cp < 0) hull_size--;
            else break;
        }
        hull[hull_size++] = points[i];
    }
    
    int s = hull_size;
    for (int i = n - 2; i >= 0; i--) {
        while (hull_size > s) {
            long long cp = cross(hull[hull_size-2], hull[hull_size-1], points[i]);
            if (collinear ? cp <= 0 : cp < 0) hull_size--;
            else break;
        }
        hull[hull_size++] = points[i];
    }
    
    return hull_size - 1;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Point *alexa = malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &alexa[i].x, &alexa[i].y);
    }
    
    if (cross(alexa[0], alexa[1], alexa[2]) < 0) {
        for (int i = 0; i < n/2; i++) {
            Point temp = alexa[i];
            alexa[i] = alexa[n-1-i];
            alexa[n-1-i] = temp;
        }
    }
    
    int k;
    scanf("%d", &k);
    
    Point *celery = malloc(k * sizeof(Point));
    for (int i = 0; i < k; i++) {
        scanf("%lld %lld", &celery[i].x, &celery[i].y);
    }
    
    Point *convex_hull = malloc(k * sizeof(Point));
    int s = monotone_chain(celery, k, convex_hull, true);
    
    int *step = malloc(n * sizeof(int));
    int *next_arr = malloc(n * sizeof(int));
    
    for (int l = 0, r = 1, d = 0; l < n; l++) {
        while (cross(alexa[l], convex_hull[d], convex_hull[(d+1)%s]) < 0 || 
               cross(alexa[l], convex_hull[d], convex_hull[(d+s-1)%s]) < 0) {
            d = (d + 1) % s;
        }
        
        while (cross(alexa[l], convex_hull[d], alexa[r]) < 0) {
            r = (r + 1) % n;
        }
        
        step[l] = (r - l - 1 + n) % n;
        next_arr[l] = (r - 1 + n) % n;
    }
    
    int blocks = ceil(sqrt(n));
    int *block_step = malloc(n * sizeof(int));
    int *jump = malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        int j = i;
        block_step[i] = 0;
        for (int _ = 0; _ < blocks; _++) {
            block_step[i] += step[j];
            j = next_arr[j];
        }
        jump[i] = j;
    }
    
    int count = n;
    for (int i = 0; i < n; i++) {
        int j = i, remaining = n - 1, c = 1;
        while (remaining >= block_step[j]) {
            remaining -= block_step[j];
            j = jump[j];
            c += blocks;
        }
        while (remaining >= step[j]) {
            remaining -= step[j];
            j = next_arr[j];
            c++;
        }
        if (c < count) count = c;
    }
    
    printf("%d\n", count);
    
    free(alexa);
    free(celery);
    free(convex_hull);
    free(step);
    free(next_arr);
    free(block_step);
    free(jump);
    
    return 0;
}