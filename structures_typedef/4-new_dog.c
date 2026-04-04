#include <string.h>
#include "dog.h"

/**
 * new_dog - creates a new dog
 * @name: the name of the dog
 * @age: the age of the dog
 * @owner: the owner of the dog
 *
 * Return: pointer to the new dog, or NULL on failure
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *dog;
	unsigned int i;

	dog = malloc(sizeof(dog_t));
	if (!dog)
		return (NULL);

	dog->name = malloc(strlen(name) + 1);
	if (!dog->name)
	{
		free(dog);
		return (NULL);
	}

	dog->owner = malloc(strlen(owner) + 1);
	if (!dog->owner)
	{
		free(dog->name);
		free(dog);
		return (NULL);
	}

	for (i = 0; name[i]; i++)
		dog->name[i] = name[i];
	dog->name[i] = '\0';

	for (i = 0; owner[i]; i++)
		dog->owner[i] = owner[i];
	dog->owner[i] = '\0';

	dog->age = age;

	return (dog);
}
