#include "main.h"

void find_program(char *buf)
{
    char *path, *duplicate, *token, **p;
    char initial_path[20] = "/bin/";
    int i;
    pid_t child;
    int status;
    char sep[] = "\n ";
    
    duplicate = strdup(buf);
    token = _strtok(duplicate, sep);
    if (token == NULL)
    {
        free(duplicate);
        return;
    }
    path = malloc(strlen(token) + strlen(initial_path) + 1);
    if (strchr(token, '/') == NULL)
    {
        if (_strcmp(token, "cd") == 0)
        {
            _chdir(buf);
            return;
        } else
        if (strcmp(token, "exit") == 0)
        {
            token = _strtok(NULL, sep);
            if (token == NULL)
            {
                kill(getppid(), SIGINT);
                kill(getpid(), SIGINT);
            } 
            else
                exit(atoi(token));
            return;
        } else if (strcmp(token, "env") == 0)
        {
            _printenv();
            return;
        } else if (strcmp(token, "setenv") == 0)
        {
            _setenv(_strtok(NULL, sep), _strtok(NULL, sep), 1);
            return;
        } else if (strcmp(token, "unsetenv") == 0)
        {
            _unsetenv(_strtok(NULL, sep));
            return;
        }
        strcat(initial_path, token);
        path = initial_path;
    } else
        path = (token);
    p = malloc(sizeof(char *) * (strlen(buf) + 1));
    if (p == NULL)
    {
        perror("Memory allocation failed\n");
        free(duplicate);
        free(path);
        return;
    }
    p[0] = path;
    for (i = 1; (token = _strtok(NULL, sep)) != NULL; i++)
    {
        p[i] = token;
    }
    p[i] = NULL;


    child = fork();

    if (child == -1)
    {
        perror("Can't create a child process\n");
    } else if (child == 0)
    {
        _execve(path, p, environ);
    } else
    {
        wait(&status);
        free(duplicate);
        free(p);
    }
}
