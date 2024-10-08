#include "main.h"

#define PATH_MAX 4096
/**
 * _builtins - function to add builtin commands
 * Return: commands
 */

int _builtins(void)
{
	return (sizeof(builtins) / sizeof(struct builtin));
}
/**
 * _exit - function to exit
 * @args: arguments
 */

void my_exit(char **args)
{
	int status = 0;
	int stat_val;
	const char *msg;

	if (args[1] != NULL)
	{
		if (_strtol(args[1], &stat_val) != 0 || stat_val < 0 || stat_val > 255)
		{
			msg = "exit: invalid status\n";
			write(STDERR_FILENO, msg, sizeof(msg) - 1);
			return; /* Exit with failure status */
		}
		status = stat_val;
	}

	exit(status);
}

/**
 * _cd - change directory
 * @args: arguments
 */

void my_cd(char **args)
{
	const char *home_dir = getenv("HOME");
	const char *oldpwd = getenv("OLDPWD");
	const char *pwd = getenv("PWD");
	const char *msg;
	char current_dir[PATH_MAX];
	char *target_dir = NULL;

	if (args[1] == NULL)
	{
		/* No argument provided, use HOME */
		target_dir = (home_dir != NULL) ? home_dir : "/";
	}
	else if (strcmp(args[1], "-") == 0)
	{
		/* if argument is "-", use OLDPWD */
		target_dir = (oldpwd != NULL) ? oldpwd : "/";
	}
	else
	{
		target_dir = args[1];
	}

	if (pwd != NULL)
	{
		if (setenv("OLDPWD", pwd, 1) != 0)
		{
			msg = "cd: failed to set OLDPWD\n";
			perror(msg);
			return;
		}
	}

	if (chdir(target_dir) != 0)
	{
		msg = "cd: failed to set OLDPWD\n";
		perror(msg);
		return;
	}
	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
	{
		if (setenv("PWD", current_dir, 1) != 0)
		{
			msg = "cd: failed to set PWD";
			perror(msg);
		}
	}
	else
	{
		msg = "cd: failed to get current directory";
		perror(msg);
	}
}
