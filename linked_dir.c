#include "main.h"

location* linked_dir()
{
    char *env = _getenv("PWD");
    DIR *dir = opendir("/");
    location *head;
    
    head = malloc(sizeof(location));
    if (head == NULL)
    {
        perror("Can't initiate memory location of the head node");
        kill(getpid(), SIGINT);
    }
    if (dir == NULL)
    {
        perror("Can't open the root directory\n");
        kill(getpid(), SIGINT);
    }
    head->dir = dir;
    head->path = env;
    head->next = NULL;
    return(head);
}
