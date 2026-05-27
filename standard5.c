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