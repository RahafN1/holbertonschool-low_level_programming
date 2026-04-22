#include "lists.h"

/**
 * free_list - frees all nodes of a list
 * @head: pointer to head node
 *
 * Return: void
 */
void free_list(list_t *head)
{
    list_t *node;
    list_t *next_node;

    if (head == NULL)
        return;

    node = head;

    while (node)
    {
        next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }
}
