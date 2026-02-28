#include "main.h"

/**
 * print_last_digit - prints the last digit of a number
 * @n: The number
 *
 * Return: value of the last digit
 */
int print_last_digit(int n)
{
	int last;

	if (n < 0)
		last = -(n % 10);
	else
		last = n % 10;
	_putchar(last + '0');
	return (last);
}
