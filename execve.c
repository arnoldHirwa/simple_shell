#include "main.h"

int _execve(const char *file, char *const *argv, char *const *env)
{
    int n;

    if ((n = execve(file, argv, env)) == -1)
    {
        perror("./shell");
    }
    return n;
}
