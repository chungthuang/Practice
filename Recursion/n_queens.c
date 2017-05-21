// gcc -Wall -o n_queens n_queens.c
#include <stdio.h>
#include <assert.h> 
#include <stdlib.h>

#define N 10
#define INDEX(row,col) row*N+col


void print_board(int board[])
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(board[INDEX(i,j)])
			{
				printf("q ");
			}
			else
			{
				printf("x ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

// Only need to check the left of col
int is_safe(int board[], int row, int col)
{
	// Check if there is any other queen on this row
	int i = row, j;
	for(j = 0; j < col; j++)
	{
		if(board[INDEX(row,j)])
		{
			return 0;
		}
	}

	// Upper diagonal
	i = row-1;
	j = col-1;
	while(i >= 0 && j >= 0)
	{
		if(board[INDEX(i,j)])
		{
			return 0;
		}
		i--;
		j--;
	}

	// Lower diagoanl
	i = row+1;
	j = col-1;
	while(i < N && j >=0)
	{
		if(board[INDEX(i,j)])
		{
			return 0;
		}
		i++;
		j--;
	}

	// Pass all check
	return 1;
}

int n_queens(int board[], int col, int* sol_count)
{
	if(col == N)
	{
		if(*sol_count == 0)
		{
			print_board(board);
		}
		(*sol_count)++;
		return 1;
	}
	for(int row = 0; row < N; row++)
	{
		if(is_safe(board,row,col))
		{
			board[INDEX(row,col)] = 1;
			n_queens(board,col+1,sol_count);
			board[INDEX(row,col)] = 0;
		}
	}
	return 0;
}


int main(int argc, char* argv[])
{

	int board[N*N] = {0};
	int sol_count = 0;
	n_queens(board, 0, &sol_count);
	printf("There are %d solutions for %d-queens problem\n", sol_count, N);
	return 0;
}