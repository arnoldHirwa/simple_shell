#include "main.h"

/**
 * exec_command - Execute a command
 * @original: The original command string
 *
 * Return: 1 on success, -1 on failure
 */
int exec_command(char *original)
{
    char *path, *duplicate, *token, **p;
    char initial_path[20] = "/bin/";
    int i;
    char sep[] = "\n ";

    duplicate = strdup(original);
    token = _strtok(duplicate, sep);

    if (token == NULL)
    {
        free(duplicate);
        return (-1);
    }

    path = malloc(strlen(token) + strlen(initial_path) + 1);

    if (strchr(token, '/') == NULL)
    {
        strcat(initial_path, token);
        path = initial_path;
    }
    else
    {
        path = token;
    }

    p = malloc(sizeof(char *) * (strlen(original)) + 1);

    if (p == NULL)
    {
        perror("Memory allocation failed\n");
        free(duplicate);
        free(path);
        return (-1);
    }

    p[0] = path;

    for (i = 1; (token = _strtok(NULL, sep)) != NULL; i++)
    {
        p[i] = token;
    }

    p[i] = NULL;

    return (_bin(path, p, duplicate));
}
