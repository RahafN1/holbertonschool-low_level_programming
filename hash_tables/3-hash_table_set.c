#include "hash_tables.h"

/**
 * update_value - Updates the value of an existing key
 * @ht: The hash table
 * @key: The key to search for
 * @value: The new value
 * @index: The index in the array
 *
 * Return: 1 if updated, 0 if not found or failed
 */
static int update_value(hash_table_t *ht, const char *key,
		const char *value, unsigned long int index)
{
	hash_node_t *tmp;

	tmp = ht->array[index];
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(value);
			if (tmp->value == NULL)
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/**
 * hash_table_set - Adds an element to the hash table
 * @ht: The hash table
 * @key: The key - cannot be an empty string
 * @value: The value associated with the key
 *
 * Return: 1 if succeeded, 0 otherwise
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	hash_node_t *node;
	unsigned long int index;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);

	if (update_value(ht, key, value, index))
		return (1);

	node = malloc(sizeof(hash_node_t));
	if (node == NULL)
		return (0);

	node->key = strdup(key);
	if (node->key == NULL)
	{
		free(node);
		return (0);
	}
	node->value = strdup(value);
	if (node->value == NULL)
	{
		free(node->key);
		free(node);
		return (0);
	}
	node->next = ht->array[index];
	ht->array[index] = node;
	return (1);
}
