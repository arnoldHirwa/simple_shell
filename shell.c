#include "main.h"

int main()
{
    size_t len = 0;
    int n;
    char *buf;

    signal(SIGINT, handle_signal);

    while (1)
    {
        printf("{^_^} $ ");
        fflush(stdout);
        buf = malloc(1024);
        n = _getline(&buf, &len, stdin);
        if (n > 0)
        {
            find_program(buf);
            free(buf);
        }
    }
    return(0);
}
