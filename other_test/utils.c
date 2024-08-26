#include "main.h"

/**
 * Custom strlen function
 */
size_t custom_strlen(const char *str)
{
    size_t length = 0;
    while (str[length] != '\0')
        length++;
    return length;
}

/**
 * Custom strdup function
 */
char *custom_strdup(const char *s)
{
    size_t len = custom_strlen(s) + 1;
    char *dup = malloc(len);
    if (dup == NULL)
        return NULL;
    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];
    return dup;
}

/**
 * Custom strcmp function
 */
int custom_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

/**
 * Custom strncmp function
 */
int custom_strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
        n--;
    }
    if (n == 0)
        return 0;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

/**
 * Custom strncpy function
 */
char *custom_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}

/**
 * Custom strtok function
 */
char *custom_strtok(char *str, const char *delim)
{
    static char *saved_str;
    if (str)
        saved_str = str;
    if (!saved_str || *saved_str == '\0')
        return NULL;

    char *start = saved_str;
    while (*saved_str)
    {
        const char *d = delim;
        while (*d)
        {
            if (*saved_str == *d)
            {
                *saved_str++ = '\0';
                if (saved_str == start)
                {
                    start++;
                    continue;
                }
                return start;
            }
            d++;
        }
        saved_str++;
    }
    return start;
}

/**
 * Custom getline function
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
    if (*lineptr == NULL)
    {
        *n = 128;  // Initial buffer size
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
            return -1;
    }

    size_t i = 0;
    int c;

    while ((c = fgetc(stream)) != EOF)
    {
        if (i >= *n - 1)
        {
            *n *= 2;
            char *new_lineptr = realloc(*lineptr, *n);
            if (new_lineptr == NULL)
                return -1;
            *lineptr = new_lineptr;
        }

        (*lineptr)[i++] = (char)c;

        if (c == '\n')
            break;
    }

    if (c == EOF && i == 0)
        return -1;

    (*lineptr)[i] = '\0';
    return i;
}

/**
 * Function to split the input line into arguments
 */
char **split_line(char *line)
{
    int bufsize = BUFFER_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("simple_shell: allocation error");
        exit(EXIT_FAILURE);
    }

    token = custom_strtok(line, DELIMITERS);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("simple_shell: allocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = custom_strtok(NULL, DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}
