#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mnist_funcs.h"

void
reverse_bytes_int(int *n)
{
	if(n == NULL) return;
	int8_t *start = (int8_t *) n;
	int8_t *end = (int8_t *) n + 3;
	int8_t tmp;
	for(int i = 0; i < 2; ++i) {
		tmp = *end;
		*end = *start;
		*start = tmp;
		start++; end--;
	}
}
