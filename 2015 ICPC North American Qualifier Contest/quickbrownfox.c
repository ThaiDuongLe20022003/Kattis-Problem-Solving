#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // consume newline
    
    for(int i = 0; i < n; i++) {
        bool letters[26] = {false};
        
        char s[1000];
        fgets(s, sizeof(s), stdin);
        int used = 0;
        
        for(int j = 0; s[j] != '\0'; j++) {
            char c = s[j];
            int temp = tolower(c) - 'a';
            if(temp < 26 && temp >= 0 && !letters[temp]) {
                letters[temp] = true;
                used++;
            }
        }
        
        if(used == 26) {
            printf("pangram");
        } else {
            printf("missing ");
            for(int j = 0; j < 26; j++) {
                if(!letters[j]) {
                    printf("%c", (char)(j + 'a'));
                }
            }
        }
        
        printf("\n");
    }
    
    return 0;
}