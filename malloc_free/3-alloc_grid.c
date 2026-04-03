#include <stdlib.h>

int **alloc_grid(int width, int height)
{
    int **tab, i, j;

    tab = malloc(sizeof(*tab) * height);

    if (width <= 0 || height <= 0 || tab == NULL)
    {
        return (NULL);
    }
    else
    {
        for (i = 0; i < height; i++)
        {
            tab[i] = malloc(sizeof(**tab) * width);
            if (tab[i] == NULL)
            {
                /* Free everything if malloc fails */
                while (i--)
                    free(tab[i]);
                free(tab);
                return (NULL);
            }
        }
    }

    return (tab);
}
