#include <stdio.h>
#include <stdlib.h>
#include "mnist_funcs.h"
#include "yann2c/matrix.h"

int main (void)
{
	int size = 0;
	char *labels = read_idx1_file("t10k-labels-idx1-ubyte", &size);

	printf("size = %i\n", size);

	free(labels);
	return 0;
}
