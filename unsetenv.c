#include "main.h"
/**
  * _unsetenv - unsetting a string(key value pair) in an environ variable
  * @name: The key in the key value pair
  * Return: 0 on succes, -1 on failure
  */
int _unsetenv(char *name)
{
	int i = 0;
	int len = _strlen(name);

	if (name == NULL)
		return (-1);
	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			return (0);
		}
		i++;
	}
	print_string("key Not Found!");
	return (-1);
}
