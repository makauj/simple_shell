#include "main.h"

/**
 * -_strncpy - copies a string up to n characters
 * @dest: destination buffer
 * @src: source string
 * @n: maximum number of characters to copy
 * Return: pointer to destination buffer
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}

/**
 * print_string - prints a string
 * @str: string to be printed
 * Return: Number of characters
 */
int print_string(char *str)
{
	if (str != NULL)
	{
		write(1, str, _strlen(str));
		return (_strlen(str));
	}
	else
	{
		perror("print string");
		return (0);
	}
}
