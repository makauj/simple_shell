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
		dest_len++;
	for (i = 0; src[i] != '\0'; i++)
		dest[dest_len++] = src[i];
	dest[dest_len++] = '\0';

	return (dest);
}
/**
  * _strdup - duplicate a string
  * @str: string to be duplicated
  * Return: duplicated copy of the string
  */
char *_strdup(char *str)
{
	char *s;
	int len = _strlen(str);
	int i = 0;

	if (str == NULL)
		return (NULL);
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
  * _strncmp - compare n no of characters in a string
  * @n: Number of characetrs to be compared
  * @str1: first string
  * @str2: second string
  * Return: 0 if the match
  */
int _strncmp(char *str1, char *str2, ssize_t n)
{
	ssize_t i;

	for (i = 0; i < n && str1[i] != '\0' && str2[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	}
	if (i < n && (str1[i] == '\0' || str2[i] == '\0'))
		return (str1[i] - str2[i]);
	return (0);
}

/**
 * _strcmp - compares two strings
 * @s1: first string to be compared
 * @s2: second string to be compared
 * Return: 0 if success, the difference of ASCII value of characters if failed
 */

int _strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
	{
		return (0);
	}
	else
	{
		return (*s1 - *s2);
	}
}
