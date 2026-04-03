#include <stdlib.h>

/**
 * free_grid - free the grid
 * @grid: grid of memories
 * @height: number of rows
 *
 * Return: void
 */
void free_grid(int **grid, int height)
{
	int i;

	if (grid == NULL || height <= 0)
		return;

	i = 0;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}
