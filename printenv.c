#include "main.h"

void _printenv()
{
    int i = 0;
    while(environ[i])
    {
        printf("%s\n", environ[i++]);
    }
}
