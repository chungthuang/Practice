// gcc -Wall -o quick_sort quick_sort.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 

void print_array(int* array, int start, int end)
{
	printf("Start:%d, End:%d\n", start, end);
	for(int i = start; i <= end; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");
}

void swap(int* array, int i, int j)
{
	int temp;
	temp = array[j];
	array[j] = array[i];
	array[i] = temp;
}

int partion(int* array, int start, int end, int pivot, int pivot_index)
{
	int i = start, j = end;
	//printf("%d,%d,%d\n",start, end, pivot_index);
	swap(array, pivot_index, end);
	while(i < j)
	{
		if(array[i] < pivot)
		{
			i++;
		}
		else 
		{
			j--;
			swap(array,i,j);
		}
	} 
	swap(array,j,end);
	//print_array(array, start, end);
	return j;
	 
}

void find_pivot(int* array, int* pivot, int* pivot_index, int start, int end)
{
	int mid = start + (end-start)/2;
	*pivot = array[end];
	*pivot_index = end;

}

void quick_sort(int* array, int start, int end)
{
	// Find pivot
	int pivot_rank, pivot, pivot_index;
	find_pivot(array, &pivot, &pivot_index, start, end);
	//printf("%d,%d\n",pivot, pivot_index);
	pivot_rank = partion(array, start, end, pivot, pivot_index);
	if(pivot_rank-1 > start)
	{
		quick_sort(array, start, pivot_rank-1);
	}
	if(pivot_rank + 1 < end)
	{
		quick_sort(array, pivot_rank+1, end);
	}
}

int main(int argc, char* argv[])
{
	int array_size;
	int *array;
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
		quick_sort(array, 0, array_size-1);
		print_array(array, 0, array_size-1);

	}	
	return 0;
}