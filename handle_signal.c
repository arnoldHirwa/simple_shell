#include "main.h"

void handle_signal(int signum)
{
    if (signum == SIGINT)
    {
        exit(1);
    }
}
