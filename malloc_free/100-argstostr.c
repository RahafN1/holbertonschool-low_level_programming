#include <stdlib.h>

/**
 * argstostr - concatenates all arguments of the program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: pointer to the new string, or NULL on failure
 */
char *argstostr(int ac, char **av)
{
	char *result;
	int total;
	int i;
	int j;
	int k;

	if (ac == 0 || av == NULL)
		return (NULL);

	total = 0;
	i = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
			j++;
		total += j + 1;
		i++;
	}

	result = malloc(sizeof(char) * (total + 1));
	if (result == NULL)
		return (NULL);

	k = 0;
	i = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			result[k] = av[i][j];
			k++;
			j++;
		}
		result[k] = '\n';
		k++;
		i++;
	}
	result[k] = '\0';

	return (result);
}
