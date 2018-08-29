// malloc-free.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>
#include <string.h>

static const char *msg[] = { "Sunday", "Mondaydfdfdf",
"Tuesday", "Wednesday",
"Thursday", "Friday", "Saturday" };

char *get_a_day(int idx)
{
	char *buf = (char*)malloc(20);
	strcpy_s(buf,19,msg[idx]);
	return buf;
}

int main(void)
{
	printf("%s %s\n", get_a_day(0), get_a_day(1));
	printf("%s\n", get_a_day(1));
	
	return 0;
}

