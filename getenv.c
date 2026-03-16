#include "main.h"
/**
  * _getenv - get the environ value
  * @name: key string to search
  * Return: value string in the key value pair
  */

char *_getenv(char *name)
{
	size_t len;
	int i = 0;

	if (name == NULL)
		return (NULL);
	len = _strlen(name);
	while (environ[i] != NULL)
	{
		if (_strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
		{
			return (environ[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}
