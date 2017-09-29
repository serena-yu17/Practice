// randomwalk.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <stdio.h>
int SIZE;
using namespace std;

typedef unsigned char byte;

byte rainbow[188][3] = {
	{ 84,0,159 },
	{ 84,0,163 },
	{ 84,0,168 },
	{ 79,0,177 },
	{ 78,0,182 },
	{ 77,0,186 },
	{ 76,0,191 },
	{ 70,0,200 },
	{ 68,0,204 },
	{ 66,0,209 },
	{ 60,0,214 },
	{ 58,0,218 },
	{ 55,0,223 },
	{ 46,0,232 },
	{ 43,0,236 },
	{ 40,0,241 },
	{ 36,0,245 },
	{ 33,0,250 },
	{ 25,0,255 },
	{ 16,0,255 },
	{ 12,0,255 },
	{ 4,0,255 },
	{ 0,0,255 },
	{ 0,4,255 },
	{ 0,16,255 },
	{ 0,21,255 },
	{ 0,25,255 },
	{ 0,29,255 },
	{ 0,38,255 },
	{ 0,42,255 },
	{ 0,46,255 },
	{ 0,51,255 },
	{ 0,63,255 },
	{ 0,67,255 },
	{ 0,72,255 },
	{ 0,84,255 },
	{ 0,89,255 },
	{ 0,93,255 },
	{ 0,97,255 },
	{ 0,106,255 },
	{ 0,110,255 },
	{ 0,114,255 },
	{ 0,119,255 },
	{ 0,127,255 },
	{ 0,135,255 },
	{ 0,140,255 },
	{ 0,152,255 },
	{ 0,157,255 },
	{ 0,161,255 },
	{ 0,165,255 },
	{ 0,174,255 },
	{ 0,178,255 },
	{ 0,182,255 },
	{ 0,187,255 },
	{ 0,195,255 },
	{ 0,199,255 },
	{ 0,216,255 },
	{ 0,220,255 },
	{ 0,225,255 },
	{ 0,229,255 },
	{ 0,233,255 },
	{ 0,242,255 },
	{ 0,246,255 },
	{ 0,250,255 },
	{ 0,255,255 },
	{ 0,255,246 },
	{ 0,255,242 },
	{ 0,255,238 },
	{ 0,255,225 },
	{ 0,255,216 },
	{ 0,255,212 },
	{ 0,255,203 },
	{ 0,255,199 },
	{ 0,255,195 },
	{ 0,255,191 },
	{ 0,255,187 },
	{ 0,255,178 },
	{ 0,255,174 },
	{ 0,255,170 },
	{ 0,255,157 },
	{ 0,255,152 },
	{ 0,255,144 },
	{ 0,255,135 },
	{ 0,255,131 },
	{ 0,255,127 },
	{ 0,255,123 },
	{ 0,255,114 },
	{ 0,255,110 },
	{ 0,255,106 },
	{ 0,255,102 },
	{ 0,255,89 },
	{ 0,255,84 },
	{ 0,255,80 },
	{ 0,255,76 },
	{ 0,255,63 },
	{ 0,255,59 },
	{ 0,255,55 },
	{ 0,255,46 },
	{ 0,255,42 },
	{ 0,255,38 },
	{ 0,255,25 },
	{ 0,255,21 },
	{ 0,255,16 },
	{ 0,255,12 },
	{ 0,255,8 },
	{ 0,255,0 },
	{ 8,255,0 },
	{ 12,255,0 },
	{ 21,255,0 },
	{ 25,255,0 },
	{ 29,255,0 },
	{ 42,255,0 },
	{ 46,255,0 },
	{ 51,255,0 },
	{ 55,255,0 },
	{ 63,255,0 },
	{ 67,255,0 },
	{ 72,255,0 },
	{ 76,255,0 },
	{ 89,255,0 },
	{ 93,255,0 },
	{ 97,255,0 },
	{ 110,255,0 },
	{ 114,255,0 },
	{ 119,255,0 },
	{ 123,255,0 },
	{ 131,255,0 },
	{ 135,255,0 },
	{ 140,255,0 },
	{ 144,255,0 },
	{ 153,255,0 },
	{ 161,255,0 },
	{ 165,255,0 },
	{ 178,255,0 },
	{ 182,255,0 },
	{ 187,255,0 },
	{ 191,255,0 },
	{ 199,255,0 },
	{ 203,255,0 },
	{ 208,255,0 },
	{ 212,255,0 },
	{ 221,255,0 },
	{ 225,255,0 },
	{ 242,255,0 },
	{ 246,255,0 },
	{ 250,255,0 },
	{ 255,255,0 },
	{ 255,250,0 },
	{ 255,242,0 },
	{ 255,238,0 },
	{ 255,233,0 },
	{ 255,229,0 },
	{ 255,221,0 },
	{ 255,216,0 },
	{ 255,212,0 },
	{ 255,199,0 },
	{ 255,191,0 },
	{ 255,187,0 },
	{ 255,178,0 },
	{ 255,174,0 },
	{ 255,170,0 },
	{ 255,165,0 },
	{ 255,161,0 },
	{ 255,153,0 },
	{ 255,148,0 },
	{ 255,144,0 },
	{ 255,131,0 },
	{ 255,127,0 },
	{ 255,119,0 },
	{ 255,110,0 },
	{ 255,106,0 },
	{ 255,102,0 },
	{ 255,97,0 },
	{ 255,89,0 },
	{ 255,85,0 },
	{ 255,80,0 },
	{ 255,76,0 },
	{ 255,63,0 },
	{ 255,59,0 },
	{ 255,55,0 },
	{ 255,51,0 },
	{ 255,38,0 },
	{ 255,34,0 },
	{ 255,29,0 },
	{ 255,21,0 },
	{ 255,17,0 },
	{ 255,12,0 },
	{ 255,0,0 }
};


struct point
{
	byte B = 210;
	byte G = 210;
	byte R = 210;
};

void writebmp(point**);

void setColor(point& pt, unsigned long count)
{
	int ratedCount = 188 * count / (SIZE*SIZE / 5);
	pt.R = rainbow[ratedCount][0];
	pt.G = rainbow[ratedCount][1];
	pt.B = rainbow[ratedCount][2];
}

void randWalk()
{
	random_device rd;
	mt19937 mtRand(rd());
	uniform_int_distribution<int> dist = uniform_int_distribution<int>(-4, 4);
	unsigned long count = 0;
	point** map = new point*[SIZE];
	for (int j = 0; j < SIZE; j++)
	{
		map[j] = new point[SIZE];
		for (int i = 0; i < SIZE; i++)
			map[j][i] = point();
	}
	int x = SIZE / 2, y = SIZE / 2;
	while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && count < SIZE*SIZE / 5)
	{
		int increX, increY;
		do {
			increX = dist(mtRand);
		} while (!increX || x + increX < 0 || x + increX >= SIZE);
		do {
			increY = dist(mtRand);
		} while (!increY || y + increY < 0 || y + increY >= SIZE);
		x += increX;
		y += increY;
		count++;
		setColor(map[y][x], count);
	}

	writebmp(map);

	for (int j = 0; j < SIZE; j++)
		delete[] map[j];
	delete[] map;
}

void writebmp(point** map)
{
	unsigned int headers[13];
	FILE * outfile;
	int extrabytes;
	int paddedsize;
	int x; int y; int n;

	extrabytes = 4 - ((SIZE * 3) % 4);                 // How many bytes of padding to add to each
														// horizontal line - the size of which must
														// be a multiple of 4 bytes.
	if (extrabytes == 4)
		extrabytes = 0;

	paddedsize = ((SIZE * 3) + extrabytes) * SIZE;

	// Headers...
	// Note that the "BM" identifier in bytes 0 and 1 is NOT included in these "headers".

	headers[0] = paddedsize + 54;      // bfSize (whole file size)
	headers[1] = 0;                    // bfReserved (both)
	headers[2] = 54;                   // bfOffbits
	headers[3] = 40;                   // biSize
	headers[4] = SIZE;  // biWidth
	headers[5] = SIZE; // biHeight

						 // Would have biPlanes and biBitCount in position 6, but they're shorts.
						 // It's easier to write them out separately (see below) than pretend
						 // they're a single int, especially with endian issues...

	headers[7] = 0;                    // biCompression
	headers[8] = paddedsize;           // biSizeImage
	headers[9] = 0;                    // biXPelsPerMeter
	headers[10] = 0;                    // biYPelsPerMeter
	headers[11] = 0;                    // biClrUsed
	headers[12] = 0;                    // biClrImportant

	outfile = fopen("./random_walk.bmp", "wb");

	//
	// Headers begin...
	// When printing ints and shorts, we write out 1 character at a time to avoid endian issues.
	//

	fprintf(outfile, "BM");

	for (n = 0; n <= 5; n++)
	{
		fprintf(outfile, "%c", headers[n] & 0x000000FF);
		fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
		fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
		fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
	}

	// These next 4 characters are for the biPlanes and biBitCount fields.

	fprintf(outfile, "%c", 1);
	fprintf(outfile, "%c", 0);
	fprintf(outfile, "%c", 24);
	fprintf(outfile, "%c", 0);

	for (n = 7; n <= 12; n++)
	{
		fprintf(outfile, "%c", headers[n] & 0x000000FF);
		fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
		fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
		fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
	}

	//
	// Headers done, now write the data...
	//

	for (y = SIZE - 1; y >= 0; y--)     // BMP image format is written from bottom to top...
	{
		for (x = 0; x <= SIZE - 1; x++)
		{
			// Also, it's written in (b,g,r) format...
			fprintf(outfile, "%c", map[y][x].B);
			fprintf(outfile, "%c", map[y][x].G);
			fprintf(outfile, "%c", map[y][x].R);
		}
		if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
		{
			for (n = 1; n <= extrabytes; n++)
			{
				fprintf(outfile, "%c", 0);
			}
		}
	}

	fclose(outfile);
	return;
}



int main()
{
	puts("Input the size desired:");
	scanf_s("%d", &SIZE);
	randWalk();
	system("./random_walk.bmp");
	return 0;
}

