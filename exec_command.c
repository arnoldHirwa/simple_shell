#include "main.h"

/* $ */

/**
 * command_forkd - forks and execute process to run command
 * @info: params & return info
 * Return: void
 */

void command_forkd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, env_return(info)) == -1)
		{
			data_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_errorput(info, "Permission denied\n");
		}
	}
}

/**
 * command_find - find the command path
 * @info: params & return info
 * Return: void
 */

void command_find(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->flag_lncount == 1)
	{
		info->count_line++;
		info->flag_lncount = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
	{
		if (!delim_true(info->arg[i], " \t\n"))
			k++;
	}
	if (!k)
		return;
	path = path_findh(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		command_forkd(info);
	}
	else
	{
		if ((interact(info) ||
			 _getenv(info, "PATH=") ||
			 info->argv[0][0] == '/') &&
			command(info, info->argv[0]))
			command_forkd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_errorput(info, "not found\n");
		}
	}
}
