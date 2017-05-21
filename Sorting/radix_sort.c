// gcc -Wall -o radix_sort radix_sort.c
#include <stdio.h>
#include <assert.h> 
#include <stdlib.h>
#include <string.h>

#define BASE 10
#define BUCKET(val,exp) (val/exp)%BASE

void print_array(int* array, int start, int end)
{
	printf("Start:%d, End:%d\n",start,end);
	for(int i = start; i <= end; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");

}

int find_max(int* array, int size)
{
	int max = array[0];
	for(int i = 1; i < size; i++)
	{
		if(max < array[i])
		{
			max = array[i];
		}
	}
	return max;
}

void count_sort(int* array, int* temp, int size, int exp)
{
	int count[BASE] = {0};
	// Histogram 
	for(int i = 0; i < size; i++)
	{
		count[BUCKET(array[i],exp)]++;
	}

	for(int i = 1; i < BASE; i++)
	{
		count[i] += count[i-1];
	}

	for(int i = size-1; i >= 0; i--)
	{
		temp[count[BUCKET(array[i],exp)]-1] = array[i];
		count[BUCKET(array[i],exp)]--;
	}

	memcpy(array, temp, sizeof(int)*size);
}

void radix_sort(int* array, int*temp, int size)
{
	int max = find_max(array, size);
	for(int exp = 1; max/exp > 0; exp*= BASE)
	{
		count_sort(array, temp, size, exp);
	}	
}

int main(int argc, char* argv[])
{
	int array_size;
	int *array, *temp;
	printf("How many elements?\n");
	scanf("%d",&array_size);
	if(array_size > 0)
	{
		array = (int*)malloc(sizeof(int)*(array_size));
		temp = (int*)malloc(sizeof(int)*(array_size));
		assert(array != NULL);
		assert(temp != NULL);
		for(int i = 0; i < array_size; i++)
		{
			scanf("%d",&(array[i]));
		}
		radix_sort(array, temp, array_size);
		print_array(array, 0, array_size-1);

	}	
	return 0;
}