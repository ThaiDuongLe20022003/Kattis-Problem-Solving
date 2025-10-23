#include <cstdio>
int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    
    if (a > b) printf("MAGA!\n");
    else if (a < b) printf("FAKE NEWS!\n");
    else printf("WORLD WAR 3!\n");
    
    return 0;
}