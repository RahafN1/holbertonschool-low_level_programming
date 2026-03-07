#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @s: string
 * Return: s
 */
char *cap_string(char *s)
{
	int i;
	int cap;

	i = 0;
	cap = 1;
	while (s[i] != '\0')
	{
		if (s[i] >= 'a' && s[i] <= 'z' && cap)
		{
			s[i] = s[i] - 32;
		}
		cap = 0;
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' ||
			s[i] == ',' || s[i] == ';' || s[i] == '.' ||
			s[i] == '!' || s[i] == '?' || s[i] == '"' ||
			s[i] == '(' || s[i] == ')' ||
			s[i] == '{' || s[i] == '}')
		{
			cap = 1;
		}
		i++;
	}
	return (s);
}
