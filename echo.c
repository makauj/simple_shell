#include "main.h"
/**
  * echo - handles variables
  * @argv: commands from the command line
  * Return: 0 if success, non zero on failure
  */
int echo(char *argv)
{
	char *var;
	char *key;
	int len = 0;
	int i = 0;
	int len1;
	char buffer[BUFFER_SIZE];
	char *temp;
	char temp1;
	pid_t pid = getpid();

	if (argv == NULL)
		return (-1);
	temp = argv;
	var = _strchr(temp, '$');
	var = var + 1;

	if (*var == '\0')
	{
		_putchar('0');
		_putchar('\n');
		return (0);
	}
	else if (*var == '$')
	{
		while (pid > 0)
		{
			buffer[i] = (pid % 10) + '0';
			pid = pid / 10;
			i++;
		}
		buffer[i] = '\0';
		len1 = _strlen(buffer);
		for (i = 0; i < len1 / 2; i++)
		{
			temp1 = buffer[i];
			buffer[i] = buffer[len1 - 1 - i];
			buffer[len1 - 1 - i] = temp1;
		}
		buffer[len1] = '\0';
		print_string(buffer);
		_putchar('\n');
		return (0);
	}
	else
	{
		len = _strlen(var);
		key = malloc(len + 1);
		if (key == NULL)
			return (-1);

		i = 0;
		while (var[i] != '\0')
		{
			key[i] = var[i];
			i++;
		}
		key[i] = '\0';
	
		i = 0;
		while (environ[i] != NULL)
		{
			if (_strncmp(environ[i], key, len) == 0 && environ[i][len] == '=')
			{
				print_string(environ[i] + len + 2);
				_putchar('\n');
				free(key);
				return (0);
			}
			i++;
		}
		free(key);
	}
	return (-1);
}
