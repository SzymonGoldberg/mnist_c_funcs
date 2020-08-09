#include <stdio.h>
#include <stdlib.h>
#include "mnist_funcs.h"
#include "yann2c/matrix.h"

int main (void)
{
	int size = 0;
	char *labels = read_idx1_file("t10k-labels.idx1-ubyte", &size);
	if(labels == NULL) return 1;

	matrix_t* a = matrix_alloc_mnist_labels(labels, size);
	if(a == NULL) { free(labels); return 1; }

	matrix_display(*a);
        matrix_free(a);
	free(labels);
	return 0;
}
