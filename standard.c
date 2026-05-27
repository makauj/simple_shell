#include "main.h"
/**
 * _strcmp - compares two strings
 * @s1: first string to be compared
 * @s2: second string to be compared
 * Return: 0 if success, the difference of ASCII value of characters if failed
 */
int _strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2) {
		s1++;
		s2++;
	}
	if (*s1 == *s2) {
		return (0);
	}
	else {
		return (*s1 - *s2);
	}
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
