#include "main.h"

/**
 * _atoi - converts a string to an integer
 * @s: the string to convert
 * Return: the integer value of the string, or 0 if no digits found
 */
int _atoi(char *s)
{
	int i;
	int sign;
	unsigned int result;
	int found;

	i = 0;
	sign = 1;
	result = 0;
	found = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] == '+')
			sign *= 1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			found = 1;
			result = result * 10 + (s[i] - '0');
		}
		else if (found == 1)
			break;
		i++;
	}
	if (sign == -1)
		return ((int)(~result + 1));
	return ((int)result);
}
