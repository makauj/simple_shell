#include "main.h"

/**
 * _strtok - function to tokenize a string
 * @str: string to be tokenized
 * @delim:string with all delimiter characters 
 *
 * Return:the token if found, else return NULL
 */

static char *last_pos = NULL;

char *_strtok(char *str, const char *delim)
{
	char *start;

	if (str)
	{
		last_pos = str;
	}
    
	if (!*last_pos)
	{
		return (NULL);
	}
	while (*last_pos && _strchr(delim, *last_pos))
	{
		last_pos++;
	}
	if (*last_pos == '\0')
	{
		last_pos = NULL;
		return (NULL);
	}

	start = last_pos;
	while (*last_pos && !_strchr(delim, *last_pos))
	{
		last_pos++;
	}

	if (*last_pos != '\0')
	{
		*last_pos = '\0';
		last_pos++;
	}
	else
	{
		last_pos = NULL;
	}

	return (start);
}

/**
 * _strchr - function that mimics strchr function
 * @str: string
 * @c: character in a string
 *
 * Return: NUll
 */
 
char *_strchr(const char *str, int c) 
{
	while (*str)
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}
