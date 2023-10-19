#include "main.h"

/**
* find_function - Find and execute a built-in function
* @token: The command token to check
* @original: The original command string
*
* Return: 0 if a built-in function is executed, 1 otherwise
*/
int find_function(char *token, char *original)
{
	char sep[] = "\n ";

	if (_strcmp(token, "cd") == 0)
	{
		_chdir(original);
		return (0);
	}
	else if (_strcmp(token, "exit") == 0)
	{
		token = strtok(NULL, sep);
		if (token == NULL)
		{
			kill(getppid(), SIGINT);
			kill(getpid(), SIGINT);
		}
		else
		{
			exit(_atoi(token));
		}
		return (0);
	}
	else if (_strcmp(token, "env") == 0)
	{
		_printenv();
		return (0);
	}
	else if (_strcmp(token, "setenv") == 0)
	{
		_setenv(strtok(NULL, sep), strtok(NULL, sep), 1);
		return (0);
	}
	else if (_strcmp(token, "unsetenv") == 0)
	{
		_unsetenv(strtok(NULL, sep));
		return (0);
	}

	return (1);
}
