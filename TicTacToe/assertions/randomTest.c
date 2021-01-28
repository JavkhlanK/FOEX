#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
    int min, max;
    srand(time(NULL));
    _sleep(200);
    /*
    printf("Min: ");
    scanf("%d", &min);
    printf("Max: ");
    scanf("%d", &max);
    */
    min = 0;
    max = 8;

    int mrand = 1 + (rand() % (max - min) + 1);
    printf("value: %d", mrand);
}