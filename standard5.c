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
	size_t bufsize;
	size_t position = 0;
	char *new_line;
	int character;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);

	bufsize = (*lineptr != NULL && *n > 0) ? *n : 128;
	if (*lineptr == NULL || *n == 0)
	{
		*lineptr = malloc(bufsize);
		if (*lineptr == NULL)
			return (-1);
		*n = bufsize;
	}

	character = EOF;
	while ((character = fgetc(stream)) != EOF)
	{
		if (position + 1 >= *n)
		{
			bufsize = *n * 2;
			new_line = realloc(*lineptr, bufsize);
			if (new_line == NULL)
				return (-1);
			*lineptr = new_line;
			*n = bufsize;
		}

		(*lineptr)[position++] = (char)character;
		if (character == '\n')
			break;
	}

	if (character == EOF && position == 0)
		return (-1);

	(*lineptr)[position] = '\0';
	return ((ssize_t)position);
}
