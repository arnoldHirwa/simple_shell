#include "main.h"

/**
 * _dataclean - restart the data struct, init info struct.
 * @info: struct of params
 * Return: void
 */

void _dataclean(info_t *info)
{
	/*restart args, argv, path, and argc to falsy values bofore proceeding*/
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * data_set - set info
 * @info: all data structure
 * @av: all arguments from main
 * Return: void
 */

void data_set(info_t *info, char **av)
{
	int i = 0;

	info->namefile = av[0]; /*keep the function name(1st arg)*/
	if (info->arg) /*if there is command*/
	{
		/*separate the arg with tab and space and update argv*/
		info->argv = _strword_a(info->arg, " \t");
		if (!info->argv) /*if no arguments*/
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				/*after successfully creating the pointer to arg, that will be only arg*/
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i; /*update the number of arguments we have*/
		/*if there is a specific alias, replace it with the real value*/
		_replacealia(info);
		/*if there is a specific variable in arguments, replace it with real data*/
		_replacevar(info);
	}
}

/**
 * data_free - free all info from struct
 * @info: struct of params
 * @all: true if free all
 * Return: void
 */

void data_free(info_t *info, int all)
{
	_freestrn(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->buf_cmd)
			free(info->arg);
		if (info->env)
			list_cleaner(&(info->env));
		if (info->history)
			list_cleaner(&(info->history));
		if (info->alias)
			list_cleaner(&(info->alias));
		_freestrn(info->environ);
		info->environ = NULL;
		pointer_free((void **)info->buf_cmd);
		if (info->fdread > 2)
			close(info->fdread);
		put_char(-1);
	}
}
