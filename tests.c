#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void
reverse_bytes_int(int *n)
{
	if(n == NULL) return;
	int8_t *start = (int8_t *) n;
	int8_t *end = (int8_t *) n + 3;
	int8_t tmp;
	for(int i = 0; i < 2; ++i)
	{
		tmp = *end;
		*end = *start;
		*start = tmp;
		start++; end--;
	}
}

int main (void)
{
	FILE* f = fopen("t10k-images.idx3-ubyte", "rb");
	if(f == NULL) return 1;

	int a;
	fread(&a, 1, sizeof(int), f);
	printf("a = %i\n", a);

	int size;
	fread(&size, 1, sizeof(int), f);
	reverse_bytes_int(&size);
	printf("size = %i\n", size);
	
	return 0;
}
