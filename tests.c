#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mnist_funcs.h"

int main (void)
{
	FILE* f = fopen("t10k-labels.idx1-ubyte", "rb");
	if(f == NULL) return 1;

	int a;
	fread(&a, 1, sizeof(int), f);
	printf("a = %i\n", a);

	int size;
	fread(&size, 1, sizeof(int), f);
	reverse_bytes_int(&size);
	printf("size = %i\n", size);

	unsigned char label;
	for(int i = 0; i < size; ++i)
	{
		fread(&label, 1, sizeof(unsigned char), f);
		printf("label = %u\n", label);
	}
	
	return 0;
}
