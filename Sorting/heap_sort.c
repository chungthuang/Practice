// gcc -Wall -o heap_sort heap_sort.c
#include <stdio.h>
#include <assert.h> 
#include <stdlib.h>

#define LEFTCHILD(i) 2*i+1
#define RIGHTCHILD(i) 2*i+2

void swap(int* array, int i, int j)
{
	int temp;
	temp = array[j];
	array[j] = array[i];
	array[i] = temp;
}

void print_array(int* array, int start, int end)
{
	printf("Start:%d, End:%d\n",start,end);
	for(int i = start; i <= end; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");

}

void heapify(int* array, int size, int root_index)
{
	int largest_index = root_index;
	if(LEFTCHILD(root_index) < size && array[LEFTCHILD(root_index)] > array[largest_index])
	{
		largest_index = LEFTCHILD(root_index);
	}
	if(RIGHTCHILD(root_index) < size && array[RIGHTCHILD(root_index)] > array[largest_index])
	{
		largest_index = RIGHTCHILD(root_index);
	}
	if(largest_index != root_index)
	{
		swap(array,largest_index,root_index);
		heapify(array, size, largest_index);
	}
}

void heap_sort(int* array, int size)
{
	// Build a max heap
	for(int i = size/2-1; i >= 0; i--)
	{
		heapify(array,size,i);
	}

	for(int i = size-1; i >= 0; i--)
	{
		
		// Swap root node with last node and delete last node from the heap
		swap(array, 0, i);
		heapify(array, i, 0);
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
		heap_sort(array, array_size);
		print_array(array, 0, array_size-1);

	}	
	return 0;
}