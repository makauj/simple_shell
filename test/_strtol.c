#include "main.h"

/**
 * _strtol - function to mimic strtol
 * @str: string
 * @value: converted string
 *
 * Return: nothing
 */

int _strtol(const char *str, int *value)
{
	int result = 0;
	int sign = 1;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	while (*str)
	{
		if (!isdigit(*str))
		{
			return (-1);
		}
	result = result * 10 + (*str - '0');
	str++;
	}

	*value = sign * result;
	return (0);
}
