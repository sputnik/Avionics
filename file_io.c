#include <stdio.h>
#include <stdlib.h>

void main() {
	FILE *file;
	file = fopen("test.txt", "w");
	fprintf(file, "This is a test file\n");
	fclose(file);
}