// gcc -Wall -o first_non_recurring first_non_recurring.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_CHARS 256
#define ALL_RECURRING -1

struct char_count
{
	int count;
	int index;
};

int first_non_recurring(char* string)
{
	struct char_count table[NUM_CHARS] = {{0}};
	int first_index = -1;
	
	for(int i = 0; *(string+i); ++i)
	{
		if(++(table[*(string+i)].count) == 1)
		{
			table[*(string+i)].index = i;	
		}
	}
	
	for(int i = 0; i < NUM_CHARS; ++i)
	{
		if(table[i].count == 1 && (table[i].index < first_index || first_index == -1))
		{
			first_index = table[i].index;
		}
	}
	return first_index;
}

int main(int argc, char* argv[])
{
	char* string;
	int str_len, index;
	printf("Please enter string length\n");
	scanf("%d",&str_len);
	assert(str_len > 0);
	string = (char*)malloc(sizeof(char)*str_len);
	printf("Please enter a string\n");
	scanf("%s",string);
	index = first_non_recurring(string);
	if(index == ALL_RECURRING)
	{
		printf("All characters are recurring\n");
	}	
	else
	{
		printf("The first non recurring character is %c\n",*(string+index));
	}
	return 0;
}