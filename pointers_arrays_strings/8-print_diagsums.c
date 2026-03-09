#include <stdio.h>
#include "main.h"

/**
 * print_diagsums - prints the sum of the two diagonals of a square matrix
 * @a: pointer to the matrix
 * @size: size of the matrix
 *
 * Return: void
 */
void print_diagsums(int *a, int size)
{
	int i;
	int diag1;
	int diag2;

	diag1 = 0;
	diag2 = 0;
	for (i = 0; i < size; i++)
	{
		diag1 += a[i * size + i];
		diag2 += a[i * size + (size - 1 - i)];
	}
	printf("%d, %d\n", diag1, diag2);
}
