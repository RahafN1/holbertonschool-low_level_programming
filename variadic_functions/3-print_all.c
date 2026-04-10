#include "variadic_functions.h"

/**
 * print_all - prints anything based on format string
 * @format: list of types of arguments passed to the function
 *
 * Return: void
 */
void print_all(const char * const format, ...)
{
	va_list args;
	unsigned int i;
	char *str;
	char sep[2];
	char c;
	int integer;
	float f;

	i = 0;
	sep[0] = '\0';
	sep[1] = '\0';
	va_start(args, format);
	while (format && format[i])
	{
		if (format[i] == 'c')
		{
			c = va_arg(args, int);
			printf("%s%c", sep, c);
			sep[0] = ',';
			sep[1] = ' ';
		}
		if (format[i] == 'i')
		{
			integer = va_arg(args, int);
			printf("%s%d", sep, integer);
			sep[0] = ',';
			sep[1] = ' ';
		}
		if (format[i] == 'f')
		{
			f = (float)va_arg(args, double);
			printf("%s%f", sep, f);
			sep[0] = ',';
			sep[1] = ' ';
		}
		if (format[i] == 's')
		{
			str = va_arg(args, char *);
			while (str == NULL)
				str = "(nil)";
			printf("%s%s", sep, str);
			sep[0] = ',';
			sep[1] = ' ';
		}
		i++;
	}
	va_end(args);
	printf("\n");
}
