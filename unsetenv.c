#include "main.h"

int _unsetenv(const char *name)
{
    int found = 0;
    int i;
    char *var, *token;

    if (name == NULL || strchr(name, '=') != NULL)
    {
        errno = EINVAL;
        perror("unsetenv");
        return -1;
    }
    for (i = 0; environ[i] != NULL; i++)
    {
        var = strdup(environ[i]);
        token = strtok(var, "=");

        if (token != NULL && strcmp(name, token) == 0)
        {
            found = 1;
        } else if (found)
        {
            environ[i - 1] = environ[i];
        }
    }

    if (found)
    {
        environ[i - 1] = NULL;
        return 0;
    } else
    {
        errno = EINVAL;
        perror("Variable not found");
        return -1;
    }
}
