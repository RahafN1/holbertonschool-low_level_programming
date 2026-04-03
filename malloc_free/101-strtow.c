#include <stdlib.h>

/**
 * count_words - counts the number of words in a string
 * @str: the string to count words in
 *
 * Return: number of words
 */
static int count_words(char *str)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

/**
 * word_len - returns the length of a word
 * @str: pointer to the start of the word
 *
 * Return: length of the word
 */
static int word_len(char *str)
{
	int len;

	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	return (len);
}

/**
 * fill_word - allocates and fills a single word
 * @str: pointer to start of word in original string
 *
 * Return: pointer to the new word, or NULL on failure
 */
static char *fill_word(char *str)
{
	char *word;
	int len;
	int j;

	len = word_len(str);
	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	j = 0;
	while (j < len)
	{
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

/**
 * strtow - splits a string into words
 * @str: the string to split
 *
 * Return: pointer to array of strings, or NULL on failure
 */
char **strtow(char *str)
{
	char **words;
	int wcount;
	int i;
	int k;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	wcount = count_words(str);
	if (wcount == 0)
		return (NULL);
	words = malloc(sizeof(char *) * (wcount + 1));
	if (words == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (k < wcount)
	{
		while (str[i] == ' ')
			i++;
		words[k] = fill_word(&str[i]);
		if (words[k] == NULL)
		{
			while (k--)
				free(words[k]);
			free(words);
			return (NULL);
		}
		while (str[i] && str[i] != ' ')
			i++;
		k++;
	}
	words[k] = NULL;
	return (words);
}
