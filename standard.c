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

	if (s == NULL)
		return (-1);
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
 * @c: charater to be located
 *Return: if successful, pointer to first occurence of character c
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
