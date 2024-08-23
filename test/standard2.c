#include "main.h"

/**
 *_strcat - concatenates two strings
 *@dest: pointer to string to be concatenated on
 *@src: source string to be appended
 *Return: pointer to destination string
 */

char *_strcat(char *dest, char *src)
{
	int i = 0, dest_len = 0;

	while (dest[i++])
	{
		dest_len++;
	}
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[dest_len++] = src[i];
	}
	dest[dest_len++] = '\0';

	return (dest);
}

/**
 * _strdup - function that duplicates strings
 * @str: string
 * 
 * Return: the string copy
 */

char *_strdup(const char *s)
{
	size_t len = _strlen(str) + 1;
	size_t i;
	char *copy = malloc(len);

	if (copy == NULL)
	{
		return(NULL);
	}
	for (i = 0; i < len; i++)
	{
		copy[i] = str[i];
	}
	return (copy);
}
