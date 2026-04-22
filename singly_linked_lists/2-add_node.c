#include "lists.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 *
 * Return: address of the new node
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new_head = malloc(sizeof(list_t));
	unsigned int i;

	if (!head || !new_head)
		return (NULL);
	if (str)
	{
		new_head->str = strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
		i = 0;
		while (new_head->str[i])
			i++;
		new_head->len = i;
	}
	else
	{
		new_head->str = NULL;
		new_head->len = 0;
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}
