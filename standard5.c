#include "main.h"
/**
  * _strdup - duplicate a string
  * @str: string to be duplicated
  * Return: duplicated copy of the string
  */
char *_strdup(char *str)
{
	char *s;
	int len;
	int i = 0;

	if (str == NULL)
		return (NULL);
	len = _strlen(str);
	s = malloc(sizeof(char) * len + 1);
	if (s == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	s[len] = '\0';
	return (s);
}
/**
  * _putchar - print a character
  * @c: character to be printed
  * Return: 1 on success
  */
int _putchar(char c) {
	if (c != '\0')
	{
		write(1, &c, 1);
		return (1);
	}
	else
		return (0);
}

/**
 * _getline - custom implementation of getline function
 * @lineptr: pointer to the buffer where the input will be stored
 * @n: pointer to the size of the buffer
 * @stream: input stream to read from
 * Return: number of characters read, or -1 on failure
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
    char *buffer;
    size_t bufsize = 0;
    ssize_t len;

    if (lineptr == NULL || n == NULL || stream == NULL)
        return (-1);

    len = getline(&buffer, &bufsize, stream);
    if (len == -1)
    {
        free(buffer);
        return (-1);
    }

    *lineptr = buffer;
    *n = bufsize;
    return (len);
}
