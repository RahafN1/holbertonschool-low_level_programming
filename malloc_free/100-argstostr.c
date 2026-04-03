#include <stdlib.h>

/**
 * get_total - calculates total length of all arguments
 * @ac: argument count
 * @av: argument vector
 *
 * Return: total length needed
 */
static int get_total(int ac, char **av)
{
	int total;
	int i;
	int j;

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
	return (total);
}

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
	int i;
	int j;
	int k;

	if (ac == 0 || av == NULL)
		return (NULL);

	result = malloc(sizeof(char) * (get_total(ac, av) + 1));
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
