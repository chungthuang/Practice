// Compile: gcc -Wall -o tower_hanoi tower_hanoi.c
#include <stdio.h>

void hanoi(int disks, int src, int dst, int tmp)
{
	// Base case
	if(disks == 1)
	{
		printf("Move disk 1 from %d to %d\n", src, dst);
		return;
	}
	hanoi(disks-1,src,tmp,dst); // Move all but the bottom disk to tmp
	printf("Move disk %d from %d to %d\n", disks, src, dst); // Move the bottom disk to dst
	hanoi(disks-1,tmp,dst,src); // Move the other disks from tmp to dst

}

int main(int argc, char *argv[])
{
	int disks;
	printf("How many disks?\n");
	scanf("%d",&disks);
	if(disks > 0)
	{
		hanoi(disks,0,2,1);
	}
	return 0;
}