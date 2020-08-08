#include <stdio.h>
#include <stdlib.h>
#include "mnist_funcs.h"
#include "yann2c/matrix.h"

void
reverse_bytes_int(int *n)
{
	if(n == NULL) return;
	unsigned char *start = (unsigned char *) n;
	unsigned char *end = (unsigned char *) n + 3;
	unsigned char tmp;
	for(int i = 0; i < 2; ++i) {
		tmp = *end;
		*end = *start;
		*start = tmp;
		start++; end--;
	}
}

//funkcja przyjmuje nazwe pliku <filename>, zczytuje z niego dane i zapisuje je
//w tablicy charow ktora alokuje i zwraca, z kolei w zmiennej <size> zapisuje ile
//danych zaalokowal
char *
read_idx1_file(const char *filename, int *size)
{
	if(filename == NULL || size == NULL) return NULL;

	FILE *f = fopen(filename, "rb");
	if(f == NULL) return NULL;

	int magic_number;
	fread(&magic_number, 1, sizeof(int), f);

	fread(size, 1, sizeof(int), f);
	reverse_bytes_int(size);
	if(!size) { fclose(f); return NULL; }

	char *result = (char *)calloc(*size, sizeof(char));
	if(result == NULL) { fclose(f); return NULL; }

	for(int i = 0; i < *size; ++i)
		fread((result + i), 1, sizeof(unsigned char), f);

	fclose(f);
	return result;
}

char *
read_idx3_file(const char *filename, int *size)
{

}

//funkcja alokuje i zwraca adres macierzy o rozmiarze
//x = 10, y = <size>. w kazdym wierszu macierzy jest oznaczona
//komorka o indeksie z <labels>
matrix_t *
matrix_alloc_mnist_labels(char *labels, int size)
{
	if(labels == NULL) return NULL;
	matrix_t* a = matrix_alloc(10, size);
	if(a == NULL) return NULL;

	for(int i = 0; i < size; ++i)
		a->matrix[*(labels + i) + i * a->y] = 1;
	return a;
}
