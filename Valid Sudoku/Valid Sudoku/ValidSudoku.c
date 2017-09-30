// ValidSudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

int isValidSudoku(char** board, int boardRowSize, int boardColSize)
{
	char row[9][10];
	char col[9][10];
	char box[9][10];
	memset(row, 0, 90);
	memset(col, 0, 90);
	memset(box, 0, 90);
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			if (isdigit(board[y][x]))
			{
				int num = board[y][x] - '0';
				if (!num)
					return 0;
				row[y][num]++;
				if (row[y][num] > 1)
					return 0;
				col[x][num]++;
				if (col[x][num] > 1)
					return 0;
				int nbox = (int)(y / 3) * 3 + (int)(x / 3);
				box[nbox][num]++;
				if (box[nbox][num] > 1)
					return 0;
			}
	return 1;
}


int main()
{
	char** board = (char**)malloc(9 * sizeof(char*));
	board[0] = ".87654321";
	board[1] = "2........";
	board[2] = "3........";
	board[3] = "4........";
	board[4] = "5........";
	board[5] = "6........";
	board[6] = "7........";
	board[7] = "8........";
	board[8] = "9........";
	for (int y = 0; y < 9; y++)
	{
		int x;
		for (x = 0; x < 8; x++)
		{
			printf("%c ", board[y][x]);
		}
		printf("%c\n", board[y][x]);
	}
	printf("\n");
	char* judgement;
	if (isValidSudoku(board, 9, 9))
		judgement = "It is a valid Sudouku.";
	else
		judgement = "It is not a valid Sudouku.";
	printf("%s\n", judgement);
	getchar();
	return 0;
}

