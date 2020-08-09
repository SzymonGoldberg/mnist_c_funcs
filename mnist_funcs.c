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

unsigned char **
read_idx3_file(const char *filename, int *size, int *image_size)
{
	if(filename == NULL || size == NULL) return NULL;

	FILE *f = fopen(filename, "rb");
	if(f == NULL) return NULL;

//zczytuje magic_number
	int magic_number;
	fread(&magic_number, 1, sizeof(int), f);

//zczytuje size
	fread(size, 1, sizeof(int), f);
	reverse_bytes_int(size);
	if(!(*size)) { fclose(f); return NULL; }

//zczytuje height
	int height, width;
	fread(&height, 1, sizeof(int), f);
	reverse_bytes_int(&height);
	if(!height) { fclose(f); return NULL; }

//zczytuje width
	fread(&width, 1, sizeof(int), f);
	reverse_bytes_int(&width);
	if(!width) { fclose(f); return NULL; }

//alokuje na tablice obrazow
	unsigned char** result = (unsigned char **)calloc(*size, sizeof(char *));
	if(result == NULL) { fclose(f); return NULL; }

//alokuje na kazdy obraz
	*image_size = width * height;
	for(int i = 0; i < *size; ++i)
	{
		*(result + i) = (unsigned char *)calloc(*image_size, sizeof(char));
		if(*(result + i) == NULL)
		{
			for(int g = i - 1; g > -1; --g) free( *(result + g));
			free(result);
			fclose(f);
			return NULL;
		}
	}

//wpisuje dane do kazdego wskaznika
	for(int i = 0; i < *size; ++i)
		fread(*(result + i), sizeof(char), *image_size, f);

	fclose(f);
	return result;
}

matrix_t *
matrix_alloc_mnist_images(const char *filename)
{
	int size, image_size;
	unsigned char **images = read_idx3_file(filename, &size, &image_size);
	if(images == NULL) return NULL;

	matrix_t* a = matrix_alloc(image_size, size);
	if(a == NULL)
	{
		for(int i = 0; i < size; ++i) free( *(images+i));
		free(images);
		return NULL;
	}
	
	for(int i = 0; i < size; ++i)
		for(int g = 0; g < image_size; ++g)
			a->matrix[g + i*a->x] = (*(*(images + i) + g) / 255.0);

	for(int i = 0; i < size; ++i) free( *(images+i));
	free(images);
	return a;
}

matrix_t *
matrix_alloc_mnist_labels(const char *filename)
{
	int size;
	char* labels = read_idx1_file(filename, &size);
	if(labels == NULL) return NULL;

	matrix_t* a = matrix_alloc(10, size);
	if(a == NULL) return NULL;

	for(int i = 0; i < size; ++i)
		a->matrix[*(labels + i) + i * a->x] = 1;

	free(labels);
	return a;
}
