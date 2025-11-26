#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int times;
    scanf("%d", &times);
    getchar(); // consume newline
    
    for(int i = 0; i < times; i++) {
        char s[256];
        fgets(s, sizeof(s), stdin);
        
        // Remove newline character
        s[strcspn(s, "\n")] = 0;
        
        if(strstr(s, "Simon says") == s) { // Check if it starts with "Simon says"
            char *result = s + 11; // Point to after "Simon says"
            printf("%s\n", result);
        }
    }
    
    return 0;
}