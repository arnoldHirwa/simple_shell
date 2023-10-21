#include "main.h"

/* $ */

/**
 * exit_all - exit the shell
 * @info: struct for potential arguments
 * Return: exit only or with status given by the user
 */

int exit_all(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = int_err(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			_errorput(info, "Ellegal number: ");
			_printstr(info->argv[1]);
			_putcharstdr('\n');
			return (1);
		}
		info->num_err = int_err(info->argv[1]);
		return (-2);
	}
	info->num_err = -1;
	return (-2);
}

/**
 * _chdi - change current dir
 * @info: struct for potential arguments
 * Return: 0 (Success)
 */

int _chdi(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		put_str("Todo: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			put_str(s);
			put_char('\n');
			return (1);
		}
		put_str(_getenv(info, "OLDPWD=")), put_char('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		_errorput(info, "Folder does not exist ");
		_printstr(info->argv[1]), _putcharstdr('\n');
	}
	else
	{
		_makenv(info, "OLDPWD", _getenv(info, "PWD"));
		_makenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
