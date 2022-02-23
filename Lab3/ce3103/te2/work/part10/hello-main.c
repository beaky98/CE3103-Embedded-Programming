#include "hello.h"
#include <stdio.h>

void delay(int timer)
{
    int i;
    for(i = 0; i < timer; ++i);
}

int main()
{
    printf("Hello World from main!\n");
    delay(0x5fffff);

    int count = 0;
    while(count < 1)
    {
            helloprint();
            count = incrementcount(count);
    }

    printf("Bye!\n");
    return 0;
}
