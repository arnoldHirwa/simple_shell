#include "main.h"

/* $ */

/**
 * env_return - return arr copy of environ
 * @info: struct of params
 * Return: 0 (Success)
 */

char **env_return(info_t *info)
{
	if (!info->environ || info->changed_env)
	{
		info->environ = list_string(info->env);
		info->changed_env = 0;
	}
	return (info->environ);
}

/**
 * _delenv - remove env variable
 * @info: struct of params
 * @var: string env property
 * Return: changed value
 */

int _delenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = start_with(node->str, var);
		if (p && *p == '=')
		{
			info->changed_env = remov_node(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->changed_env);
}

/**
 * _makenv - set new env variable
 * @info: struct of params
 * @var: string env property
 * @value: value
 * Return: 0 (Success)
 */

int _makenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);

	_strcpy(buffer, var);
	_strncat(buffer, "=");
	_strncat(buffer, value);
	node = info->env;
	while (node)
	{
		p = start_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->changed_env = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->changed_env = 1;
	return (0);
}
