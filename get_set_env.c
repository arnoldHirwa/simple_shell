#include "main.h"

/* $ */

/**
 * _findenv - print env
 * @info: struct of params
 * Return: 0 (Success)
 */

int _findenv(info_t *info)
{
	_putlist_str(info->env);
	return (0);
}

/**
 * _getenv - get the value of environment
 * @info: struct of all items
 * @name: the env. name to search
 * Return: the environment value on success, null on failure
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env; /*extract the value of env from env linked list*/
	char *curr;

	while (node)
	{
		/*search env which starts with name characters*/
		curr = start_with(node->str, name);
		if (curr && *curr) /*if you found one and it's not empty*/
			return (curr); /*return found environment value*/
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenviro - create env variable
 * @info: struct of params
 * Return: 0 (Success)
 */

int _setenviro(info_t *info)
{
	if (info->argc != 3)
	{
		_printstr("Incorrect number of arguments\n");
		return (1);
	}
	if (_makenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * un_setenviro - create env variable
 * @info: struct of params
 * Return: 0 (Success)
 */

int un_setenviro(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_printstr("To few arguments.\n");
		return (1);
	}
	for (i = 0; i <= info->argc; i++)
		_delenv(info, info->argv[i]);

	return (0);
}

/**
 * addenv_list - converts env. varaibles to a linked
 * and keep the linked list in env key of info_t struct
 * @info: struct of params
 * Return: 0 (Success)
 */

int addenv_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
