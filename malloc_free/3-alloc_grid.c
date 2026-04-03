#include <stdlib.h>

/**
 * alloc_grid - returns a pointer to a 2D array of integers
 * @width: number of columns
 * @height: number of rows
 *
 * Return: pointer to the 2D array, or NULL on failure
 */
int **alloc_grid(int width, int height)
{
	int **tab;
	int i;
	int j;

	if (width <= 0 || height <= 0)
		return (NULL);

	tab = malloc(sizeof(*tab) * height);
	if (tab == NULL)
		return (NULL);

	i = 0;
	while (i < height)
	{
		tab[i] = malloc(sizeof(**tab) * width);
		if (tab[i] == NULL)
		{
			while (i--)
				free(tab[i]);
			free(tab);
			return (NULL);
		}
		j = 0;
		while (j < width)
		{
			tab[i][j] = 0;
			j++;
		}
		i++;
	}

	return (tab);
}
