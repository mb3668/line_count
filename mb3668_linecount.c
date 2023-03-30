#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define FILE_NAME 100
int count = 0; // Global line count variable

// Name: Marcus Brigman
// netID: mb3668
// count-line: Program to tokenize user input file strings and count lines in file

void errorCheck(int val, const char *str)
{
	if (val == -1)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
}

void countFileLines(const char *fileName)
{
	// www.geeksforgeeks.org/c-program-count-number-lines-file/
	// Read file and return number of lines

	// File pointer and char to check for newline
	FILE *fp;
	//char *fileName = (char*)fileName;
	char c;

	fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		printf("Could not open file %s", fileName);
		exit(EXIT_SUCCESS);
	}

	for (c = getc(fp); c != EOF; c = getc(fp))
	{
		// Probably needs to be locked with a mutex. Called in each thread
		if (c == '\n') count = count + 1; // ASK ABOUT THIS
	}

	fclose(fp);
	printf("File %s has %d lines\n", fileName, count);
}


int main(int argc, char* argv[])
{
	// Initialize file pointer
	FILE *fp;
	// excecvp commands with wc and return line count number
	char filename[FILE_NAME];
	char c; // Stores char from file to check for newline

	// Create pthread for testing
	pthread_t id[2]; // Probably replace 2 with argc

	//pthread_create(&id[0], NULL, countFileLines, &argv[1]);
	//pthread_create(&id[1], NULL, countFileLines, &argv[2]);

	// Test passing multiple files
	for (int i = 0; i < argc-1; i++)
	{
		//scanf("%s", filename);
		countFileLines(argv[i+1]);
	}

	exit(EXIT_SUCCESS);
}
