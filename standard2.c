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
  * _strncmp - compare n no of characters in a string
  * @str1: first string
  * @str2: second string
  * @n: Number of characetrs to be compared
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
