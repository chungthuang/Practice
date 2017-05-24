// This program simulates malloc
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#define SIZE 1000
#define METADATA_SIZE sizeof(metadata_t)
#define DEBUG 1

typedef struct metadata
{
	int size;
	struct metadata* next;
	struct metadata* prev;
	int isFree; // 1 free, 0 not used
}metadata_t;

metadata_t* base = NULL;// start of heap
uint8_t memory[SIZE]; 

metadata_t* findBlock(int*prev_size, int request_bytes)
{
	metadata_t* prev_block, *curr_block = base;
	// Keep looking for the next block as long as there is a next block and this block is not free and
	// this block is not large enough
	while(curr_block && (curr_block->isFree == 0 || curr_block->size < request_bytes))
	{
		prev_block = curr_block;
		curr_block = curr_block->next;
	}
	*prev_size = prev_block->size;
	if(curr_block == NULL)
	{
		return (metadata_t*)((uint8_t*)prev_block + prev_block->size + METADATA_SIZE);
	}
	else
	{
		return curr_block;
	}
}

void splitBlock(metadata_t* start, int request_bytes)
{
	metadata_t* block = start + request_bytes + METADATA_SIZE;
	block->next = start->next;
	block->size = start->size - request_bytes - METADATA_SIZE;
	block->prev = start;
	block->isFree = 1;
	start->next = block;
}

void* allocate(int request_bytes)
{
	// FIrst time calling alloate
	if(request_bytes < 0 || request_bytes > SIZE - METADATA_SIZE)
	{
		return NULL;
	}
	metadata_t* block;
	if(base == NULL)
	{
		base = (metadata_t*)&memory;
		block = (metadata_t*)&memory;
		block->prev = NULL;
		block->next = NULL;
	}
	else
	{
		// Find the first available block
		int prev_block_size;
		block = findBlock(&prev_block_size, request_bytes);
#if DEBUG
		//printf("%p\n", last_block);
		printf("%p\n", block);
		printf("%p\n", memory);
#endif
		// Cannot find an available 
		if(((uint8_t*)block + request_bytes + METADATA_SIZE) > (memory + SIZE))
		{
			return NULL;
		}
		if(block->size > request_bytes)
		{
			splitBlock(block,request_bytes);
		}
		// First block has no previous block
		if(block == base)
		{
			block->prev = NULL;
		}
		else
		{
			block->prev = (metadata_t*)((uint8_t*)block - prev_block_size - METADATA_SIZE);	
			block->next = block->prev->next;
			block->prev->next = block;
		}
	}
	block->size = request_bytes;
	block->isFree = 0;
	return block+1;

}


// block1 is always before block2
void mergeBlock(metadata_t* block1, metadata_t* block2)
{
	block1->next = block2->next;
	block1->size += block2->size + METADATA_SIZE;
	
	// If block2 is not the last block
	if(block2->next != NULL)
	{
		block2->next->prev = block1;
	}
}

void release(void* start)
{
	if(start != NULL)
	{
#if DEBUG
		printf("%p\n", start);
#endif
		metadata_t* block = (metadata_t*)((uint8_t*)start - METADATA_SIZE);
		block->isFree = 1;
		if(block->prev != NULL && block->prev->isFree)
		{
			mergeBlock(block->prev,block);
			block = block->prev;
		}
		if(block->next != NULL && block->next->isFree)
		{
			mergeBlock(block,block->next);
		}
	}
}

int main(int argc, char* argv[])
{
	uint8_t* ptr, *ptr2, *ptr3, *ptr4;
	metadata_t* block;
	printf("Test1: allocate %d bytes. Should not be able to allocate this much. \n", SIZE);
	ptr = (uint8_t*)allocate(SIZE);
	assert(ptr == NULL);
	assert(base == NULL);
	printf("--- Pass test 1\n");
	
	printf("Test2: release NULL\n");
	release(ptr);
	assert(base == NULL);
	printf("--- Pass test 2\n");

	printf("Test3: allocate %d bytes \n", SIZE/2);
	ptr = (uint8_t*)allocate(SIZE/2);
	block = (metadata_t*)memory;
	assert(block->isFree == 0);
	assert(block->next == NULL);
	assert(block->prev == NULL);
	assert(block->size == SIZE/2);
	assert(ptr != NULL);
	assert(ptr - METADATA_SIZE == memory);
	printf("--- Pass test 3\n");

	printf("Test4: allocate another %d bytes. Should not be able to allocate this much.\n", SIZE/2);
	ptr2 = (uint8_t*)allocate(SIZE/2);
	assert(ptr2 == NULL);
	assert(base == (metadata_t*)(memory));
	printf("--- Pass test 4\n");


	printf("Test5: allocate another %d bytes \n", SIZE/2 - 2*METADATA_SIZE);
	ptr2 = (uint8_t*)allocate(SIZE/2 - 2*METADATA_SIZE);
	block = block->next;
	assert(ptr2 == (memory + SIZE/2 + 2*METADATA_SIZE));
	assert(block->next == NULL);
	assert(block->prev == (metadata_t*)(ptr - METADATA_SIZE));
	assert(block->isFree == 0);
	assert(block->size == SIZE/2 - 2*METADATA_SIZE);
	assert(base == (metadata_t*)(memory));
	printf("--- Pass test 5\n");

	printf("Test6: allocate another 1 byte. Should not be able to allocate. \n");
	ptr3 = (uint8_t*)allocate(1);
	printf("%p\n", ptr3);
	printf("%p\n", memory+SIZE);
	assert(ptr3 == NULL);
	assert(base == (metadata_t*)(memory));
	printf("--- Pass test 6\n");

	printf("Test7: release pointer 1. Should have %d free bytes now. Then allocate %d bytes. \n", SIZE/2 + METADATA_SIZE, SIZE/4);
	release(ptr);
	ptr = (uint8_t*)allocate(SIZE/4);
	assert(ptr == memory + METADATA_SIZE);
	printf("--- Pass test 7\n");

	/*
	printf("Test8: Allocate another %d bytes. \n", SIZE/2 - SIZE/4 - METADATA_SIZE);
	ptr4 = (uint8_t*)allocate(SIZE/2 - SIZE/4 - METADATA_SIZE);
	assert(ptr4 == memory + SIZE/4 + 2*METADATA_SIZE);
	printf("--- Pass test 8\n");

	printf("Test9: Allocate another 1 byte. Should fail. \n");
	ptr3 = (uint8_t*)allocate(1);
	assert(ptr3 == NULL);
	printf("--- Pass test 9\n");
	*/
	
	return 0;
}