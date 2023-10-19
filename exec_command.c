#include "main.h"

/**
* exec_command - Execute a command
* @original: The original command string
*
* Return: 1 on success, -1 on failure
*/
int exec_command(char *original)
{
	char *path, *duplicate, *token, **p;
	char initial_path[20] = "/bin/";
	int i, k;
	char sep[] = "\n ";


	duplicate = _strdup(original);
	token = strtok(duplicate, sep);
	if (token == NULL)
	{
		free(duplicate);
			return (-1);
	}
	path = malloc(_strlen(token) + _strlen(initial_path) + 1);
	if (_strchr(token, '/') == NULL)
	{
		k = find_function(token, original);
		if (k == 0)
			return (0);
		strcat(initial_path, token);
		path = initial_path;
	} else
		path = (token);
	p = malloc(sizeof(char *) * (_strlen(original) + 1));
	if (p == NULL)
	{
		perror("Memory allocation failed\n");
		free(duplicate);
		free(path);
		return (-1);
	}
	p[0] = path;
	for (i = 1; (token = strtok(NULL, sep)) != NULL; i++)
	{
		p[i] = token;
	}
	p[i] = NULL;

	return (_bin(path, p, duplicate));
}
