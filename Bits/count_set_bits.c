// gcc -Wall -o count_set_bits count_set_bits.c
#include <stdio.h>

int count_set_bits(int input)
{
	int count = 0;
	int mask = 1;
	while(mask <= input)
	{
		if(mask & input)
		{
			count++;
		}
		mask <<= 1;
	}
	return count;
}

int brian_kernighan(int input)
{
	int count = 0;
	while(input)
	{
		input &= input-1;
		count++;
	}
	return count;
}

int main(int argc, char* argv[])
{
	int input, count = 0;
	printf("Input a number\n");
	scanf("%d",&input);
	count = count_set_bits(input);
	printf("By naive algorithm algorithm %d\n", count);
	count = brian_kernighan(input);
	printf("By Brain Kernighan algorithm %d\n", count);
	return 0;
}