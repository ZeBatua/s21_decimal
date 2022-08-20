#include <stdio.h>

int main() {
    float f = 1.5;
    int counter = 0;
    unsigned int fbits = *((unsigned int *)&f);
    for (unsigned int mask = 0x80000000; mask ;mask >>= 1, counter++) {
        if (counter == 9) {
            printf(" ");
        } 
        if (counter == 1) {
            printf(" ");
        }    
        printf("%d", !!(fbits&mask));
    }
    printf("\n");
    return(0);
}


int main() {
    int a;
    int b;
    scanf("%d %d", &a, &b);
    int c = a ^ b;

    printf("%d\n", c);

    return(0);
}

int main() {
    int a;
    scanf("%d", &a);
    int c = ~a;

    printf("%d\n", c);

    return(0);
}

0 0 0 0 1 0 1 0 = 10
0 0 0 0 1 0 0 1 = 9
0 0 0 0 1 0 0 0 = 8