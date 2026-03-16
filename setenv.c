#include "main.h"
/**
  * _setenv - modify or add a key value variable in the environ variable
  * @name: key part of the variable
  * @value: value part of the variable
  * Return: 0 on success, -1 on failure
  */
int _setenv(char *name, char *value)
{
	if (name == NULL)
		return (-1);
	if (value == NULL)
		return (-1);
	if (name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);
	return (setenv(name, value, 1));
}
