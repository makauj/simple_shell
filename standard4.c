#include "main.h"

/**
 * *_strcpy - copies the string pointed to by src
 * @dest: value to evaluate
 * @src: value to evaluate
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * _strchr - locates a character in a string
 * @s: string to be searched
 * @c: character to be located
 * Return: if successful, pointer to first occurence of character c
 */

char *_strchr(char *s, char c)
{
	int i;

	if (s == NULL)
		return (NULL);
	for (i = 0; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
			return (&s[i]);
	}
	return (0);
}

/**
 * _strtok - tokenizes a string based on a delimiter
 * @str: string to be tokenized
 * @delim: delimiter to be used for tokenization
 * Return: pointer to the next token, or NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delim)
{
    static char *saveptr;
    char *token;

    if (str != NULL)
        saveptr = str;
    else if (saveptr == NULL)
        return (NULL);

    token = saveptr;
    while (*token && strchr(delim, *token))
        token++;

    if (*token == '\0')
    {
        saveptr = NULL;
        return (NULL);
    }

    saveptr = token + 1;
    while (*saveptr && !strchr(delim, *saveptr))
        saveptr++;

    if (*saveptr)
    {
        *saveptr = '\0';
        saveptr++;
    }
    else
        saveptr = NULL;

    return (token);
}
