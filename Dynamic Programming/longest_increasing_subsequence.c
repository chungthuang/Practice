// gcc -Wall -o longest_increasing_subsequence longest_increasing_subsequence.c
#include <stdio.h>
#include <assert.h> 
#include <stdlib.h>


int longest_increasing_subsequence(int* array, int n)
{
	// list is the longest increasing subsequence of array[i:n]
	int* lis = (int*)malloc(sizeof(int)*n);
	for(int i = 0; i < n; i++)
	{
		lis[i] = 1;
	}
	for(int i = n-1; i >= 0; i--)
	{
		for(int j = i+1; j < n; j++)
		{
			if(array[j] > array[i] && 1+lis[j] > lis[i])
			{
				lis[i] = 1 + lis[j];
			}
		}
	}
	return lis[0];
}

int improve_longest_increasing_subsequence(int* array, int n)
{
	// list is the longest increasing subsequence of array[i:n]
	int* lis = (int*)malloc(sizeof(int)*n);
	for(int i = 0; i < n; i++)
	{
		lis[i] = 1;
	}
	for(int i = n-1; i >= 0; i--)
	{
		for(int j = i+1; j < n; j++)
		{
			if(array[j] > array[i] && 1+lis[j] > lis[i])
			{
				lis[i] = 1 + lis[j];
			}
		}
	}
	return lis[0];
}



int main(int argc, char* argv[])
{
	int array_size, lis;
	int *array, *sequence;
	printf("How many elements?\n");
	scanf("%d",&array_size);
	if(array_size > 0)
	{
		array = (int*)malloc(sizeof(int)*(array_size));
		assert(array != NULL);
		for(int i = 0; i < array_size; i++)
		{
			scanf("%d",&(array[i]));
		}
		lis = improve_longest_increasing_subsequence(array, array_size);
		printf("LIS is %d \n", lis);
	}	
	return 0;
}