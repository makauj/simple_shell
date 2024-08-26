#include "main.h"

/**
 * Function to print all environment variables
 */
void print_env(void)
{
    for (char **env = environ; *env != NULL; env++)
    {
        write(STDOUT_FILENO, *env, custom_strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
    }
}

/**
 * Function to find the full path of a command
 */
char *find_command(const char *command)
{
    char *path = getenv("PATH");
    char *path_dup = custom_strdup(path); // Duplicate the PATH string
    char *dir = custom_strtok(path_dup, ":");
    char *full_path = malloc(BUFFER_SIZE);

    while (dir != NULL)
    {
        snprintf(full_path, BUFFER_SIZE, "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0) // Check if the command is executable
        {
            free(path_dup);
            return full_path; // Command found in this directory
        }
        dir = custom_strtok(NULL, ":");
    }

    free(full_path);
    free(path_dup);
    return NULL; // Command not found in any directory in PATH
}

/**
 * Function to set an environment variable
 */
void set_env(const char *name, const char *value)
{
    size_t name_len = custom_strlen(name);
    size_t value_len = custom_strlen(value);
    size_t env_len = name_len + value_len + 2; // +1 for '=' and +1 for '\0'

    char *env_entry = malloc(env_len);
    if (!env_entry)
    {
        perror("simple_shell: allocation error");
        return;
    }

    for (size_t i = 0; i < name_len; i++)
        env_entry[i] = name[i];
    env_entry[name_len] = '=';
    for (size_t i = 0; i < value_len; i++)
        env_entry[name_len + 1 + i] = value[i];
    env_entry[env_len - 1] = '\0';

    for (int i = 0; environ[i] != NULL; i++)
    {
        if (custom_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            environ[i] = env_entry; // Modify existing variable
            return;
        }
    }

    // If the variable does not exist, add a new one
    int env_count;
    for (env_count = 0; environ[env_count] != NULL; env_count++)
        ;

    char **new_environ = malloc((env_count + 2) * sizeof(char *));
    if (!new_environ)
    {
        perror("simple_shell: allocation error");
        free(env_entry);
        return;
    }

    for (int i = 0; i < env_count; i++)
    {
        new_environ[i] = environ[i];
    }
    new_environ[env_count] = env_entry;
    new_environ[env_count + 1] = NULL;
    environ = new_environ;
}

/**
 * Function to unset an environment variable
 */
void unset_env(const char *name)
{
    size_t name_len = custom_strlen(name);

    for (int i = 0; environ[i] != NULL; i++)
    {
        if (custom_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            for (int j = i; environ[j] != NULL; j++)
            {
                environ[j] = environ[j + 1];
            }
            return;
        }
    }
}
