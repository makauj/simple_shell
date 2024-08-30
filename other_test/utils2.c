#include "main.h"

/**
 * concat_path - function to mimic snprintf
 * @fp: full path
 * @dir: directory location
 * @command: command
 */

void concat_path(char *fp, const char *dir, const char *command)
{
	while (*dir != '\0')
	{
		*fp++ = *dir++;
	}

	if (*(fp - 1) != '/')
	{
		*fp++ = '/';
	}

	while (*command != '\0')
	{
		*fp++ = *command++;
	}

	*fp = '\0';
}
