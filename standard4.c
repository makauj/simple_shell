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
    static char *saved_str;
    char *start;
    const char *d;

    if (str != NULL)
        saved_str = str;
    if (saved_str == NULL)
        return (NULL);

    while (*saved_str != '\0')
    {
        d = delim;

        while (*d != '\0' && *saved_str != *d)
            d++;
        if (*d == '\0')
            break;
        saved_str++;
    }

    if (*saved_str == '\0')
    {
        saved_str = NULL;
        return (NULL);
    }

    start = saved_str;
    while (*saved_str != '\0')
    {
        d = delim;

        while (*d != '\0')
        {
            if (*saved_str == *d)
            {
                *saved_str = '\0';
                saved_str++;
                return (start);
            }
            d++;
        }
        saved_str++;
    }
    saved_str = NULL;
    return (start);
}

/**
 * _fgetc - custom implementation of fgetc function
 * @stream: input stream to read from
 * Return: the character read, or EOF on failure
 */
int _fgetc(FILE *stream)
{
	char c;
	ssize_t bytes_read;

	if (stream == NULL)
		return (EOF);

	bytes_read = read(fileno(stream), &c, 1);
	if (bytes_read == 1)
		return ((unsigned char)c);

	return (EOF);
}
