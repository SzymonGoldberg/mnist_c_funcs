#include <stdio.h>
#include <stdlib.h>
#include "mnist_funcs.h"
#include "yann2c/matrix.h"

int main (void)
{
	matrix_t* a = matrix_alloc_mnist_labels("t10k-labels.idx1-ubyte");
	if(a == NULL) return 1;

	matrix_t* b = matrix_alloc_mnist_images("t10k-images.idx3-ubyte");
	if(b == NULL) { matrix_free(a); return 1; }

        matrix_free(a);
	matrix_free(b);
	return 0;
}
