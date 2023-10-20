#include "main.h"

/**
* _bin - Execute a binary file
* @path: The path to the binary file
* @p: The array of parameters for the binary file
* @duplicate: A duplicate of the input string
*
* Return: 1 on success, -1 on failure
*/
int _bin(char *path, char **p, char *duplicate)
{
	char initial_path[20] = "/bin/";
	int k, found;
	pid_t child;
	int status, exit_status;

	found = file_exist(path);
	if (found == false)
	{
		_printstr(path);
		_printstr(": not found\n");
		return (-1);
	}
	child = fork();
	if (child == -1)
		return (_perro("child process"));
	else if (child == 0)
	{
		k = execve(path, p, environ);
		if (k == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		wait(&status);
		free(duplicate);
		free(p);
		p = NULL;
		_strcpy(initial_path, "/bin/");
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status == 0)
				return (1);
		}
	}
	return (-1);
}
