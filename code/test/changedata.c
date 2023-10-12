//
// Created by tnoulens on 9/18/23.
//

/*
 * this program changes a byte in a file at a given position
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		fprintf(stderr, "Usage: %s <filename> <position> <new_byte>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	const char *filename = argv[1];
	off_t position = atoll(argv[2]);
	unsigned char new_byte = atoi(argv[3]);
	FILE *file = fopen(filename, "r+");
	if (file == NULL)
	{
		perror("Failed to open file");
		exit(EXIT_FAILURE);
	}
	if (fseek(file, position, SEEK_SET) != 0)
	{
		perror("Failed to seek to position");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	if (fputc(new_byte, file) == EOF)
	{
		perror("Failed to write new byte");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	fclose(file);
	printf("Byte at position %ld changed to 0x%02x\n", position, new_byte);
	return 0;
}

