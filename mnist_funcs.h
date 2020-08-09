#ifndef _MNIST_FUNCS_H_
#define _MNIST_FUNCS_H_
#include "yann2c/matrix.h"

//funkcja przyjmuje nazwe pliku <filename>, zczytuje z niego dane i zapisuje je
//w tablicy charow ktora alokuje i zwraca, z kolei w zmiennej <size> zapisuje ile
//danych zaalokowal
char * read_idx1_file(const char *filename, int *size);

//funkcja zczytuje z pliku ilosc obrazow (<size>) i ich rozmiar (<image_size>)
//alokuje pamiec i zczytuje do niej dane po czym zwraca dane w formie wskaznika na 
//tablice stringow, w przypadku niepowodzenia zwraca NULL
unsigned char ** read_idx3_file(const char *filename, int *size, int *image_size);

//funkcja zczytuje dane z pliku <filename> i zwraca gotowa do uczenia macierz
//wypelniona obrazami z pliku, w przypadku niepowodzenia zwraca NULL
matrix_t * matrix_alloc_mnist_images(const char *filename);

//funckja zczytuje dame z pliku <filename> i zwraca gotowa do uczenia macierz
//w przypadku niepowodzenia zwraca NULL
matrix_t * matrix_alloc_mnist_labels(const char *filename);

#endif
