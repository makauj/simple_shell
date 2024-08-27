#include "main.h"
/**
  * print_environ - print the current environment
  * Return: 0 if succesful , non zero for failure
  */
int print_environ()
{
	int i = 0;

	while (environ[i] != NULL)
	{
		print_string(environ[i]);
		print_string("\n");
		i++;
	}
	return(0);
}
