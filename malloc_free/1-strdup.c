#include <stdlib.h>

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 *           which contains a copy of the string given as a parameter
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string, or NULL on failure
 */
char *_strdup(char *str)
{
	char *dup;
	int len;
	int i;

	if (str == NULL)
		return (NULL);

	len = 0;
	while (str[len])
		len++;

	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);

	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}

	dup[len] = '\0';

	return (dup);
}
