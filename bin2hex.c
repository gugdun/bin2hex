#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

enum {
	NOT_ENOUGH_ARGS = 1,
	FAILED_TO_OPEN_INPUT,
	FAILED_TO_OPEN_OUTPUT,
	FAILED_MALLOC
};

char hexchars[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

int main(int argc, char** argv)
{
	// show usage if less than 2 arguments passed
	if (argc < 3) {
		printf("Usage: bin2hex INPUT OUTPUT [BYTES_PER_LINE]\n");
		return NOT_ENOUGH_ARGS;
	}

	// set hex bytes per line count in output file
	int bytes_per_line = 10;
	if (argc > 3) bytes_per_line = atoi(argv[3]);

	// open input file
	FILE* infile = fopen(argv[1], "rb");
	if (!infile) {
		printf("Failed to open input file %s\n", argv[1]);
		return FAILED_TO_OPEN_INPUT;
	}

	// get input file size
	fseek(infile, 0L, SEEK_END);
	size_t fsize = ftell(infile);
	fseek(infile, 0L, SEEK_SET);

	// allocate memory to read input file
	uint8_t* buffer = (uint8_t*)malloc(fsize);
	if (!buffer) {
		printf("Failed to allocate %zu bytes of memory\n", fsize);
		fclose(infile);
		return FAILED_MALLOC;
	}

	// read input file
	fread((void*)buffer, fsize, 1, infile);

	// close input file
	fclose(infile);

	// open output file
	FILE* outfile = fopen(argv[2], "wb");
	if (!outfile) {
		printf("Failed to open output file %s\n", argv[2]);
		return FAILED_TO_OPEN_OUTPUT;
	}

	// write text to output file
	for (size_t i = 0; i < fsize; ++i) {
		char output[3];
		output[0] = hexchars[(buffer[i] & 0xF0) >> 4];
		output[1] = hexchars[buffer[i] & 0x0F];
		output[2] = ' ';
		if ((i + 1) % bytes_per_line == 0) output[2] = '\n';
		fwrite((void*)output, 3, 1, outfile);
	}

	// close output file and exit
	fclose(outfile);
	return 0;
}
