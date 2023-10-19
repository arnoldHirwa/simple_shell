#include "main.h"

/**
 * _unsetenv - Unset an environment variable
 * @name: The name of the variable to unset
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	int found = 0;
	int i;
	char *var, *token;

	if (name == NULL || strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		perror("unsetenv");
		return (-1);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		var = strdup(environ[i]);
		token = strtok(var, "=");

		if (token != NULL && strcmp(name, token) == 0)
		{
			/* free(environ[i]); // Free the memory for the variable */
			found = 1;
		}
		else if (found)
		{
			environ[i - 1] = environ[i];
		}
	}

	if (found)
	{
		environ[i - 1] = NULL; /* Mark the last element as NULL */
		return (0);
	}
	else
	{
		errno = EINVAL;
		perror("Variable not found");
		return (-1);
	}
}

