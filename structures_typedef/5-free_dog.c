#include "dog.h"

/**
 * free_dog - frees a dog
 * @d: pointer to the dog to free
 */
void free_dog(dog_t *d)
{
	if (!d)
		return;

	free(d->name);
	free(d->owner);
	free(d);
}
