#include "main.h"

/**
* gohome - Change the current working directory to the user's home directory
* @dirs: A pointer to the location structure to keep track of directories
*
* Return: 0 on success, -1 on failure
*/
int gohome(location *dirs)
{
	char cwdir[1024] = "";
	int changed;

	if (strcmp(_getenv("PWD"), _getenv("HOME")) == 0)
	{
		return (-1);
	}

	_setenv("PWD", _getenv("HOME"), 1);
	changed = chdir(_getenv("HOME"));

	if (changed == -1)
	{
		perror("bash cd");
		return (-1);
	}

	getcwd(cwdir, 1024);
	add_dir(dirs, cwdir);

	return (0);
}

/**
* goback - Change the current working directory to a specific path
* @dirs: A pointer to the location list
* @path: The path to change to
*
* Description:
* This function changes the current working directory to the specified path
* and updates the environment variable "PWD" accordingly. If the directory
* change is unsuccessful, it returns -1; otherwise, it returns 0.
*
* Return: 0 on success, -1 on failure
*/
int goback(location *dirs, char *path)
{
	char cwdir[1024] = "";
	int changed;
	location *current = NULL;

	while (current != NULL)
		current = current->next;

	_strcat(cwdir, _getenv("PWD"));
	_strcat(cwdir, "/");
	_strcat(cwdir, path);
	current = dirs;
	changed = chdir(cwdir);

	if (changed == -1)
	{
		perror("bash: cd");
		return (-1);
	}

	_setenv("PWD", getcwd(cwdir, 1024), 1);
	add_dir(dirs, cwdir);

	return (0);
}

/**
* _chdir - Change the current working directory
* @buf: The path to the new directory
*
* Description:
* This function changes the current working directory to the specified path.
* If no path is provided, it changes the directory to the home directory.
* If the path is "-", it switches to the previous directory.
*/
void _chdir(char *buf)
{
	char *sep = "\n ";
	char *path = _strtok(buf, sep);
	static int num = 1;
	int changed;
	static location *dirs;
	location *current = NULL;

	path = _strtok(NULL, sep);
	if (num == 1)
	{
		dirs = malloc(sizeof(location));
		dirs = linked_dir();
		num++;
	}
	current = dirs;
	while (current != NULL)
		current = current->next;
	if (path == NULL)
	{
		gohome(dirs);
	}
	else if (_strcmp(path, "-") != 0)
	{
		goback(dirs, path);
	}
	else
	{
		current = dirs;
		while (current->next->next != NULL)
			current = current->next;
		_setenv("PWD", current->path, 1);
		add_dir(dirs, _getenv("PWD"));
		changed = chdir(current->path);
		if (changed == -1)
		{
			perror("bash: cd");
			return;
		}
	}
}
