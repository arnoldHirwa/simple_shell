#include "main.h"

/**
 * add_dir - Add a directory to the location list
 * @link: A pointer to the location list
 * @path: The path of the directory to add
 *
 * Description:
 * This function adds a directory to the location list by allocating memory
 * for a new location structure and initializing its properties. If the
 * allocation fails or the directory cannot be opened, it reports an error.
 */
void add_dir(location *link, char *path)
{
	location *current;
	location *tmp;
	char *opened_dir;

	if (link == NULL)
	{
		perror("invalid link");
		return;
	}
	current = link;
	while (current != NULL)
		current = current->next;
	current = link;
	while (current->next != NULL)
		current = current->next;
	tmp = malloc(sizeof(location));
	if (tmp == NULL)
	{
		perror("malloc tmp");
		return;
	}
	opened_dir = _strdup(path);
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
		current = current->next;
}
