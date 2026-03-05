#include "main.h"

/**
 * puts_half - prints the second half of a string
 * followed by a new line
 * @str: the string to print
 */
void puts_half(char *str)
{
	int i;
	int len;
	int start;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	if (len % 2 == 0)
		start = len / 2;
	else
		start = (len + 1) / 2;
	i = start;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
	_putchar('\n');
}
