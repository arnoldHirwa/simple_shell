#include "main.h"

/**
* concatenate - Concatenate strings
* @new_var: The destination buffer
* @name: The first string
* @equal: The second string
* @value: The third string
*/
void concatenate(char *new_var, char *name, char *equal, char *value)
{
	_strcpy(new_var, name);
	_strcat(new_var, equal);
	_strcat(new_var, value);
}
/**
* _perro - Print an error message and return -1
* @c: The error message to print
*
* This function prints an error message using perror() and returns -1.
*
* Return: Always returns -1.
*/
int _perro(char *c)
{
	perror(c);
	return (-1);
}

/**
* _setenv - Set or update an environment variable
* @name: The name of the variable
* @value: The value to assign to the variable
* @overwrite: If 1, overwrite the variable if it already exists; if 0, keep it
*
* Return: 0 on success, -1 on failure
*/
int _setenv(const char *name, const char *value, int overwrite)
{
	int i;
	char *var, *token, *new_var;

	if (name == NULL || _strchr((char *)name, '=') != NULL || value == NULL)
	{
		errno = EINVAL;
		return (_perro("setenv"));
	}
	for (i = 0; environ[i]; i++)
	{
		var = _strdup(environ[i]);
		token = strtok(var, "=");
		if (token != NULL && _strcmp((char *)name, (char *)token) == 0)
		{
			if (overwrite != 0)
			{
				new_var = malloc(_strlen((char *)name) + 1 + _strlen((char *)value) + 1);
				if (new_var == NULL)
				{
					perror("malloc");
					free(var);
					return (-1);
				}
				concatenate((char *)new_var, (char *)name, "=", (char *)value);
				environ[i] = new_var;
				free(var);
			}
			return (0);
		}
		free(var);
	}
	new_var = malloc(_strlen((char *)name) + 1 + _strlen((char *)value) + 1);
	if (new_var == NULL)
	{
		return (_perro("malloc"));
	}
	concatenate((char *)new_var, (char *)name, "=", (char *)value);
	environ[i] = new_var;
	environ[i + 1] = NULL;
	return (0);
}
