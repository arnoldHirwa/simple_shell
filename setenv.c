#include "main.h"

int _setenv(const char *name, const char *value, int overwrite)
{
    int i;
    char *var, *token, *new_var;

    if (name == NULL || strchr(name, '=') != NULL || value == NULL)
    {
        errno = EINVAL;
        perror("setenv");
        return -1;
    }

    for (i = 0; environ[i]; i++)
    {
        var = strdup(environ[i]);

        token = _strtok(var, "=");
        if (token != NULL && strcmp(name, token) == 0)
        {
            if (overwrite != 0)
            {
                new_var = malloc(strlen(name) + strlen(value) + 2);
                sprintf(new_var, "%s=%s", name, value);
                environ[i] = new_var;
                free(var);
            }
            return 0;
        }
        free(var);
    }
    new_var = malloc(strlen(name) + strlen(value) + 2);
    sprintf(new_var, "%s=%s", name, value);
    environ[i] = new_var;
    environ[i + 1] = NULL; 

    return 0;
}
