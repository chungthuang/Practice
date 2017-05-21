// gcc -Wall -o merge_sort merge_sort.c
#include <stdio.h>
#include <assert.h> 
#include <string.h>
#include <stdlib.h>

void print_array(int* array, int start, int end)
{
	printf("Start:%d, End:%d\n",start,end);
	for(int i = start; i <= end; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");

}

void merge(int* array, int start, int mid, int end, int* temp)
{
	int i = start, j = mid+1; // i is left array pointer and j is right array pointer
	memcpy(&(temp[start]),&(array[start]),sizeof(int)*(end-start+1));
	//printf("mid:%d\n",mid);
	//print_array(temp, start, end);
	//print_array(array, start, end);
	for(int k = start; k <= end; k++)
	{
		if(i > mid || (j <= end && temp[i] > temp[j]))
		{
			array[k] = temp[j];
			j++;
		}
		else
		{
			array[k] = temp[i];
			i++;
		}
	}
	//print_array(array, start, end);

}

void merge_sort(int* array, int start, int end, int* temp)
{
	int mid;
	mid = start+(end-start)/2; // Numerically stable way for adding 2 numbers
	if(mid > start)
	{
		merge_sort(array, start, mid, temp); // sort left array
	}
	if(mid+1 < end)
	{
		merge_sort(array, mid+1, end, temp); // sort right array
	}
	merge(array, start, mid, end, temp);

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
		merge_sort(array, 0, array_size-1, temp);
		print_array(array, 0, array_size-1);

	}	
	return 0;
}