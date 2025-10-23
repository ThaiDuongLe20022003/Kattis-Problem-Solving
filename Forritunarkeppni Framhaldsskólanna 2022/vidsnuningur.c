#include <stdio.h>

int main() {
    char str[1001];
    scanf("%s", str);
    
    // Find length without strlen
    int len = 0;
    while (str[len] != '\0') len++;
    
    // Reverse using pointer arithmetic
    char *start = str;
    char *end = str + len - 1;
    
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    
    printf("%s\n", str);
    return 0;
}