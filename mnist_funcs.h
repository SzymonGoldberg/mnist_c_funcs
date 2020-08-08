#ifndef _MNIST_FUNCS_H_
#define _MNIST_FUNCS_H_
#include "yann2c/matrix.h"

char * read_idx1_file(const char *filename, int *size);
matrix_t * matrix_alloc_mnist_labels(char *labels, int size);

#endif
