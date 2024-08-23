#include "main.h"
/**
  * _putchar - print a character
  * @c: character to be printed
  * Return: 1 on success
  */
int _putchar(char c)
{
	if (&c != NULL)
	{
		write(1, &c, 1);
		return (1);
	}
	else
		return (0);
}
/**
  *_strlen - returns the lenght of the string
  *@s: takes in character s as parameter
  *Return: returns leght as an int
  */
int _strlen(char *s)
{
	int length = 0;

	while (*s != '\0')
	{
		length++;
		s++;
	}
	return (length);
}
/**
  * print_string - prints a string
  * @str: string to be printed
  * Return: Number of characters
  */
int print_string(char *str)
{
	const char *msg;

	if (str != NULL)
	{
		write(1, str, _strlen(str));
		return (_strlen(str));
	}
	else
	{
		msg = "print string";
		write(STDERR_FILENO, msg, _strlen(msg));
		return (0);
	}
}
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
