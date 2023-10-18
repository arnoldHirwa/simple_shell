#include "main.h"

void add_dir(location* link,char *path)
{
    location* current;
    location* tmp;
    char *opened_dir;
    if (link == NULL)
    {
        perror("invalid link");
        return;
    }
    current = link;
    while (current != NULL)
    {
        current = current->next;
    }
    current = link;
    while (current->next != NULL)
    {
        current = current->next;
    }
    tmp = malloc(sizeof(location));
    if (tmp == NULL)
    {
        perror("malloc tmp");
        return;
    }
    opened_dir = strdup(path);
    tmp->dir = opendir(opened_dir);
    if (tmp->dir == NULL)
    {
        perror("tmp->dir");
        exit(98);
    }
    tmp->path = opened_dir;
    tmp->next = NULL;
    current->next = tmp;
    current = link;
    while (current != NULL)
    {
        current = current->next;
    }
}
