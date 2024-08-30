#include "main.h"

/**
 * print_env - Function to print all environment variables
 */
void print_env(void)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		write(STDOUT_FILENO, *env, custom_strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * find_command - Function to find the full path of a command
 * @command: command
 * Return: path, else NULL
 */
char *find_command(const char *command)
{
	char *path = getenv("PATH");
	char *path_dup = custom_strdup(path);
	char *dir = custom_strtok(path_dup, ":");
	char *full_path = malloc(BUFFER_SIZE);

	while (dir != NULL)
	{
	
		concat_path(full_path, dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_dup);
			return (full_path);
		}
		dir = custom_strtok(NULL, ":");
	}

	free(full_path);
	free(path_dup);
	return (NULL);
}

/**
 * set_env - Function to set an environment variable
 * @name: name
 * @value: value
 *
 * Return: nothing
 */
void set_env(const char *name, const char *value)
{
	size_t name_len = custom_strlen(name);
	size_t value_len = custom_strlen(value);
	size_t env_len = name_len + value_len + 2;
	char *env_entry = malloc(env_len);
	char **new_environ;
	int i = 0, env_count;

	if (!env_entry)
	{
		perror("simple_shell: allocation error");
		return;
	}

	for (i = 0; i < name_len; i++)
		env_entry[i] = name[i];
	env_entry[name_len] = '=';
	for (i = 0; i < value_len; i++)
		env_entry[name_len + 1 + i] = value[i];
	env_entry[env_len - 1] = '\0';

	for (i = 0; environ[i] != NULL; i++)
	{
		if (custom_strncmp(environ[i], name, name_len) == 0)
		{
		       if (environ[i][name_len] == '=')
		       {
			       environ[i] = env_entry;
			       return;
		       }
		}
	}

	for (env_count = 0; environ[env_count] != NULL; env_count++);
	new_environ = malloc((env_count + 2) * sizeof(char *));
	if (!new_environ)
	{
		perror("simple_shell: allocation error");
		free(env_entry);
		return;
	}

	for (i = 0; i < env_count; i++)
	{
		new_environ[i] = environ[i];
	}
	new_environ[env_count] = env_entry;
	new_environ[env_count + 1] = NULL;
	environ = new_environ;
}

/**
 * unse_env - Function to unset an environment variable
 * @name: name
 *
 * Return: Nothing
 */
void unset_env(const char *name)
{
	size_t name_len = custom_strlen(name);
	int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (custom_strncmp(environ[i], name, name_len) == 0)
		{
		       if (environ[i][name_len] == '=')
		       {
			       for (j = i; environ[j] != NULL; j++)
			       {
				       environ[j] = environ[j + 1];
			       }
			       return;
		       }
		}
	}
}
