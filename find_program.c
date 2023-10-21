#include "main.h"

/* $ */

/**
 * command - determins if file an execut command
 * @info: info struct
 * @path: path of the file
 * Return: 1 (Success), 0 (Fail)
 */

int command(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * char_dupl - duplicats chars
 * @pathstr: path string
 * @start: starting index
 * @stop: stoppping index
 * Return: pointer to the new buffer
 */

char *char_dupl(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffer[k++] = pathstr[i];

	buffer[k] = 0;
	return (buffer);
}

/**
 * path_findh - finds command path string
 * @info: info struct
 * @pathstr: path string
 * @cmd: command to find
 * Return: full path if found or null
 */

char *path_findh(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && start_with(cmd, "./"))
	{
		if (command(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = char_dupl(pathstr, curr_pos, i);
			if (!*path)
				_strncat(path, cmd);
			else
			{
				_strncat(path, "/");
				_strncat(path, cmd);
			}
			if (command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
