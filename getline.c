#include "main.h"

#define BUFFSIZE 1024
size_t _getline(char **buf, size_t *len, FILE *source)
{
    int read_res;
    int n = 0;
    char buff[1];

    if (source == NULL)
    {
        perror("Invalid file");
        return (-1);
    }
    while (1)
    {
        read_res = read(STDIN_FILENO, &buff, 1);

        if (read_res == -1)
        {
            perror("read_res");
            exit(98);
            return (0);
        }
        if (n > (int)(*len - 1))
        {
            *len += BUFFSIZE;
            *buf = _realloc(*buf,*len - BUFFSIZE, *len);
            if (*buf == NULL)
            {
                perror("realloc");
                exit(98);
            }
        }
        
        if (*buff == '\n')
        {
            (*buf)[n] = '\0';
            break;
        }
        else
        {
            (*buf)[n] = buff[0];
            n++;
        }
    }
    *len = n;
    return (n);
}
