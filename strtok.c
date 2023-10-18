#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *_strtok(char *str, char *sep)
{
    static char *full_str, *token;
    static int i = 0;
    int initial_i = 0, j, k;

    if (str == NULL)
    {
        initial_i = i;
    } else
    {
        i = 0;
        full_str = malloc(strlen(str) + 1);
        if (full_str == NULL)
        {
            perror("malloc full_str or string");
            exit(98);
        }
        strcpy(full_str, str);
    }
    for (;(full_str[i] != '\0') || (i == (int)strlen(full_str)); i++)
    {
        for (j = 0; (sep[j] != '\0') || (i == (int)strlen(full_str)); j++)
        {
            if (full_str[i] == sep[j])
            {
                if (i == initial_i)
                {
                    initial_i ++;
                    break;
                }
                k = i - initial_i + 1;
                token = malloc(k-1);
                if (token == NULL)
                {
                    perror("malloc token");
                    exit(98);
                }
                for (j = 0; j < (k-1); j++, initial_i++)
                    token[j] = full_str[initial_i];
                token[j] = '\0';
                
                if (i + 1 == k)
                {
                    strcpy(str, token);
                }
                i++; /*increment i so that next iteration will start on an element which is not a separator*/
                return(token);
            }
        }
    }
    return NULL;
}
