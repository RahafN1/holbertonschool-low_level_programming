#include <stdio.h>
#include "dog.h"

/**
 * print_dog - prints a struct dog
 * @d: pointer to the struct dog to print
 */
void print_dog(struct dog *d)
{
	if (!d)
		return;

	printf("Name:\t%s\n", d->name ? d->name : "(nil)");
	printf("Age:\t%f\n", d->age);
	printf("Owner:\t%s\n", d->owner ? d->owner : "(nil)");
}
