#include "hash_tables.h"

/**
 * shash_table_create - Creates a sorted hash table
 * @size: The size of the array
 *
 * Return: A pointer to the newly created hash table, or NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;
	unsigned long int i;

	if (size == 0)
		return (NULL);

	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->size = size;
	ht->shead = NULL;
	ht->stail = NULL;

	ht->array = malloc(sizeof(shash_node_t *) * size);
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	for (i = 0; i < size; i++)
		ht->array[i] = NULL;

	return (ht);
}

/**
 * create_node - Creates a new sorted hash node
 * @key: The key
 * @value: The value
 *
 * Return: A pointer to the new node, or NULL on failure
 */
static shash_node_t *create_node(const char *key, const char *value)
{
	shash_node_t *node;

	node = malloc(sizeof(shash_node_t));
	if (node == NULL)
		return (NULL);

	node->key = strdup(key);
	if (node->key == NULL)
	{
		free(node);
		return (NULL);
	}

	node->value = strdup(value);
	if (node->value == NULL)
	{
		free(node->key);
		free(node);
		return (NULL);
	}

	node->next = NULL;
	node->sprev = NULL;
	node->snext = NULL;

	return (node);
}

/**
 * insert_sorted - Inserts a node into the sorted linked list
 * @ht: The sorted hash table
 * @node: The node to insert
 */
static void insert_sorted(shash_table_t *ht, shash_node_t *node)
{
	shash_node_t *tmp;

	if (ht->shead == NULL)
	{
		ht->shead = node;
		ht->stail = node;
		return;
	}

	tmp = ht->shead;
	while (tmp && strcmp(node->key, tmp->key) > 0)
		tmp = tmp->snext;

	if (tmp == NULL)
	{
		node->sprev = ht->stail;
		ht->stail->snext = node;
		ht->stail = node;
		return;
	}

	node->snext = tmp;
	node->sprev = tmp->sprev;

	if (tmp->sprev)
		tmp->sprev->snext = node;
	else
		ht->shead = node;

	tmp->sprev = node;
}

/**
 * update_node - Updates value of existing key in sorted hash table
 * @ht: The sorted hash table
 * @key: The key to search for
 * @value: The new value
 * @index: The bucket index
 *
 * Return: 1 if updated, 0 if not found or failed
 */
static int update_node(shash_table_t *ht, const char *key,
		const char *value, unsigned long int index)
{
	shash_node_t *tmp;

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
 * shash_table_set - Adds an element to the sorted hash table
 * @ht: The sorted hash table
 * @key: The key - cannot be an empty string
 * @value: The value associated with the key
 *
 * Return: 1 if succeeded, 0 otherwise
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *node;
	unsigned long int index;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);

	if (update_node(ht, key, value, index))
		return (1);

	node = create_node(key, value);
	if (node == NULL)
		return (0);

	node->next = ht->array[index];
	ht->array[index] = node;

	insert_sorted(ht, node);

	return (1);
}

/**
 * shash_table_get - Retrieves a value associated with a key
 * @ht: The sorted hash table
 * @key: The key to look for
 *
 * Return: The value associated with the key, or NULL if not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *tmp;
	unsigned long int index;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);

	tmp = ht->array[index];
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}

	return (NULL);
}

/**
 * shash_table_print - Prints a sorted hash table
 * @ht: The sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *tmp;
	int first;

	if (ht == NULL)
		return;

	first = 1;
	printf("{");
	tmp = ht->shead;
	while (tmp)
	{
		if (first == 0)
			printf(", ");
		printf("'%s': '%s'", tmp->key, tmp->value);
		first = 0;
		tmp = tmp->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Prints a sorted hash table in reverse order
 * @ht: The sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *tmp;
	int first;

	if (ht == NULL)
		return;

	first = 1;
	printf("{");
	tmp = ht->stail;
	while (tmp)
	{
		if (first == 0)
			printf(", ");
		printf("'%s': '%s'", tmp->key, tmp->value);
		first = 0;
		tmp = tmp->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - Deletes a sorted hash table
 * @ht: The sorted hash table
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *tmp, *next;

	if (ht == NULL)
		return;

	tmp = ht->shead;
	while (tmp)
	{
		next = tmp->snext;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}

	free(ht->array);
	free(ht);
}
