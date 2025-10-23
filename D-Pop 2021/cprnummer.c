#include <stdio.h>

int main() {
    char cpr[12];
    scanf("%s", cpr);
    
    int sum = 4*(cpr[0]-48) + 3*(cpr[1]-48) + 2*(cpr[2]-48) + 7*(cpr[3]-48) + 
              6*(cpr[4]-48) + 5*(cpr[5]-48) + 4*(cpr[7]-48) + 3*(cpr[8]-48) + 
              2*(cpr[9]-48) + 1*(cpr[10]-48);
    
    putchar((sum % 11 == 0) ? '1' : '0');
    putchar('\n');
    
    return 0;
}