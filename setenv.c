#include "main.h"
/**
  * _setenv - modify or add a key value variable in the environ variable
  * @name: key part of the variable
  * @value: value part of the variable
  * Return: 0 on success, -1 on failure
  */
int _setenv(char *name, char *value)
{
	char *new;
	int i = 0;
	int len = _strlen(name);

	if (name == NULL)
		return(-1);
	if (value == NULL)
		return (-1);
	new = malloc(_strlen(name) + _strlen(value) + 2);
	if (new == NULL)
		return (-1);

	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			environ[i] = new;
			return (0);
		}
		i++;
	}
	environ[i] = new;
	environ[i + 1] = NULL;
	return (0);
}
