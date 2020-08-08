#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	FILE* f = fopen("t10k-images.idx3-ubyte", "rb");
	if(f == NULL) return 1;

	int a;
	fread(&a, 1, sizeof(int), f);
	printf("a = %i\n", a);

	int size;
	fread(&size, 1, sizeof(int), f);
	printf("size = %i\n", size);
	
	return 0;
}
