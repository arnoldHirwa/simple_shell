#include "main.h"

/* $ */

/**
 * find_histor - display history
 * @info: struct contains all arguments
 * Return: 0 (Success)
 */

int find_histor(info_t *info)
{
	pri_list(info->history);
	return (0);
}

/**
 * _unsetalia - unset alias
 * @info: struct contains all arguments
 * @str: alias string
 * Return: 0 (Success), 1 (Fail)
 */

int _unsetalia(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strlocate(str, '=');
	if (!p)
		return (1);

	c = *p;
	*p = 0;
	ret = remov_node(&(info->alias),
								get_nodeid(info->alias,
												begin_node(info->alias, str, -1)));
	*p = c;

	return (ret);
}

/**
 * _setalia - set alias
 * @info: struct contains all arguments
 * @str: alias string
 * Return: 0 (Success), 1 (Fail)
 */

int _setalia(info_t *info, char *str)
{
	char *p;

	p = _strlocate(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_unsetalia(info, str));

	_unsetalia(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _putalia - print alias
 * @node: alias linked list
 * Return: 0 (Success), 1 (Fail)
 */

int _putalia(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strlocate(node->str, '=');
		for (a = node->str; a <= p; a++)
			put_char(*a);

		put_char('\'');
		put_str(p + 1);
		put_str("'\n");
		return (0);
	}
	return (1);
}

/**
 * find_alia - alias built
 * @info: struct contains all arguments
 * Return: 0 (Success)
 */

int find_alia(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_putalia(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 0; info->argv[i]; i++)
	{
		p = _strlocate(info->argv[i], '=');
		if (p)
			_setalia(info, info->argv[i]);
		else
			_putalia(begin_node(info->alias, info->argv[i], '='));
	}
	return (0);
}
