#include "hello.h"
#include <stdio.h>

int incrementcount(int count)
{	
	printf("Hello world from funct2!\n");    
	delay(0x7fffffff);
	return count + 1;
}
