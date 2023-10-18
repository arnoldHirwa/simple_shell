#include "main.h"

char *_getenv(const char *name)
{
    char *token;
    char *env;
    int i = 0;

    for (;environ[i]; i++)
    {
        env = strdup(environ[i]);
        token = _strtok(env, "=");
        if (_strcmp(name, token) == 0)
        {
            token = _strtok(NULL, "=");
            return(token);
        }
        free(env);
    }
    return NULL;
}
