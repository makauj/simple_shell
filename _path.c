#include "main.h"

/**
 * command_path - function that searches through directories listed in PATH
 * @command: full path of the command
 *
 * Return: NULL
 */

char *command_path(const char *command)
{
	char *path = getenv("PATH");
	char *path_cpy;
	char *dir;
	char fullpath[BUFFER_SIZE];

	struct stat statbuf;

	if (path = NULL)
	{
		handle_error("getenv");
		exit(EXIT_FAILURE);
	}

	path_cpy = strdup(path);
	if (path_cpy = NULL)
	{
		handle_error("strdup");
		exit(EXIT_FAILURE);
	}
	dir = strtok(path_cpy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), %s%s, dir, command);
		if (stat(full_path, &statbuf) == 0)
		{
		       if (S_ISEREG(ststbuf.st_mode))
		       {
			      if ((statbuf.st_mode & SIXUSR))
			      {
				      free(path_cpy);
				      return (strdup(full_path));
			      }
		       }
		}
		dir = strtok(NULL, ":");
	}
	free(path_cpy);
	return (NULL);
}
