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
	char fp[BUFFER_SIZE];
	size_t dir_len, cmd_len, total_len;
	struct stat sb;

	if (path == NULL)
	{
		handle_error("getenv");
		exit(EXIT_FAILURE);
	}

	path_cpy = strdup(path);
	if (path_cpy == NULL)
	{
		handle_error("strdup");
		exit(EXIT_FAILURE);
	}
	dir = strtok(path_cpy, ":");
	while (dir != NULL)
	{
		dir_len = strlen(dir);
		cmd_len = strlen(command);
		total_len = dir_len + cmd_len + 2;

		if (total_len >= sizeof(fp))
		{
			dir = strtok(NULL, ":");
			continue;
		}

		memcpy(fp, dir, dir_len);
		fp[dir_len] = '/';
		memcpy(fp + dir_len + 1, command, cmd_len);
		fp[total_len - 1] = '\0';

		if (stat(fp, &sb) == 0)
		{
			if (S_ISEREG(sb.st_mode))
			{
				if ((sb.st_mode & SIXUSR))
				{
					free(path_cpy);
					return (strdup(fp));
				}
			}
		}
		dir = strtok(NULL, ":");
	}
	free(path_cpy);
	return (NULL);
}
