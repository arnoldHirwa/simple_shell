#include "main.h"

/**
 * _getenv - Get the value of an environment variable
 * @name: The name of the environment variable to retrieve
 *
 * Description:
 * This function searches for the environment variable with the specified name
 * and returns its value. If the variable is not found, it returns NULL.
 *
 * Return: a string pointer to the environment on sucess, NULL on failure
 */
char *_getenv(const char *name)
{
	char *token;
	char *env;
	int i = 0;

	for (; environ[i]; i++)
	{
		env = strdup(environ[i]);
		token = _strtok(env, "=");

		if (_strcmp(name, token) == 0)
		{
			token = _strtok(NULL, "=");
			return (token);
		}
		free(env);
	}
	return (NULL);
}
