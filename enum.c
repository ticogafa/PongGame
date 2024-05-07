#include <stdio.h>

typedef enum {
    RED,    // 0
    GREEN,  // 1
    BLUE    // 2
} Color;

typedef enum {
    JAN = 1,
    FEB = 2,
    MAR = 3,
    // ...
    DEC = 12
} Month;

int main() {
    Color myColor = RED;  // Usa o enum para definir uma cor
    printf("My color is: %d\n", myColor);
    Month myMonth = MAR;
    printf("My month is: %d\n", myMonth);
    return 0;
}