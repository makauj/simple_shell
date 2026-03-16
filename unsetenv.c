#include "main.h"
/**
  * _unsetenv - unsetting a string(key value pair) in an environ variable
  * @name: The key in the key value pair
  * Return: 0 on succes, -1 on failure
  */
int _unsetenv(char *name)
{
	if (name == NULL)
		return (-1);
	if (name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);
	return (unsetenv(name));
}
