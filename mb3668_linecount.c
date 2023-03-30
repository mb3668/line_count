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
	// Create error checking functionality
	if (val == -1)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
}

void *countFileLines(void *fileName)
{
	// www.geeksforgeeks.org/c-program-count-number-lines-file/
	// Read file and return number of lines

	// File pointer and char to check for newline
	FILE *fp;

	char c;
	const char* file = (char*)fileName;
	int localLineCount = 0;

	fp = fopen(file, "r");

	if (fp == NULL)
	{
		printf("Could not open file %s", file);
		exit(EXIT_SUCCESS);
	}

	// Loop through file
	for (c = getc(fp); c != EOF; c = getc(fp))
	{
		// Count newlines
		if (c == '\n')
		{
			localLineCount++; // Find exact file lines
		}
	}

	// Set global count variable. Probably needs to be in a mutex
	count = localLineCount + count;

	fclose(fp);
	printf("File %s has %d lines\n", file, localLineCount);

	return NULL;
}


int main(int argc, char* argv[])
{
	// excecvp commands with wc and return line count number
	char filename[FILE_NAME];
	char c; // Stores char from file to check for newline
	int requiredThreads = argc-1; // Finds out how many threads are required

	// Create as many pthreads as required
	pthread_t id[requiredThreads];

	// Produce threads
	for (int i = 0; i < requiredThreads; i++)
	{
		pthread_create(&id[i], NULL, countFileLines, argv[i+1]);
	}

	// Wait for threads to finish
	for (int i = 0; i < requiredThreads; i++)
	{
		pthread_join(id[i], NULL);
	}

	printf("%d total\n", count);
	// Exit main
	printf("Exiting main program\n");

	exit(EXIT_SUCCESS);
}
