#include "main.h"

/**
 * serie - test if curr char in buffer
 * @info: struct
 * @buf: the char buffer
 * @p: adress the current position
 * Return: 1 if chai delim, 0 if not
 */

int serie(info_t *info, char *buf, size_t *p)
{
	size_t i = *p;

	/*i is used to update the current position to help to read only command*/
	/*by skipping specific operators and replcing them with null*/
	if (buf[i] == '|' && buf[i + 1] == '|') /*if there is or operator*/
	{
		buf[i] = 0;
		i++;
		info->buf_cmd_type = 1; /*update the structure*/
	}
	else if (buf[i] == '&' && buf[i + 1] == '&') /*if there is and operator*/
	{
		buf[i] = 0;
		i++;
		info->buf_cmd_type = 2; /*update the structure*/
	}
	else if (buf[i] == ';') /*if there is command separator operator*/
	{
		buf[i] = 0;
		info->buf_cmd_type = 3; /*update the structure*/
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * check_serie - check and continue serieing
 * @info: struct
 * @buf: char buffer
 * @p: adress current pos
 * @i: starting pos in buf
 * @len: len of buffer
 * Return: Nothing
 */

void check_serie(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->buf_cmd_type == 2) /*if there is and (&&) signal*/
	{
		if (info->status) /*if the status of executing command*/
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->buf_cmd_type == 1) /*if there is or command*/
	{
		if (!info->status) /*if not status of executing command*/
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * _replacealia - replace aliases in tokenize string
 * @info: params
 * Return: 0, 0 if not
 */

int _replacealia(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		/*get alias that start with first arg from main*/
		node = begin_node(info->alias, info->argv[0], '=');
		if (!node) /*if not found*/
			return (0);
		free(info->argv[0]); /*release the previous one to be updated with real one*/
		p = _strlocate(node->str, '='); /*first occurence of =*/
		if (!p)
			return (0);
		p = _strdup(p + 1); /*duplicate alias after skipping = char*/
		if (!p) /*if it fails return*/
			return (0);
		info->argv[0] = p; /*replace the alias*/
	}
	return (0); /*this should be one from description*/
}

/**
 * _replacevar - replace variable in string with real value
 * @info: all data struct
 * Return: 0 always
 */

int _replacevar(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++) /*iterate through all variables*/
	{
		/*if var doesn't start with $ or there is no var to check, continue*/
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))/*check if there ? for status*/
		{
			/*update status (base 10), create duplicate, replace arg with duplicate*/
			stri_replce(&(info->argv[i]),
						_strdup(changenb(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))/*handle $ to get process id*/
		{
			stri_replce(&(info->argv[i]),
						_strdup(changenb(getpid(), 10, 0)));
			continue;
		}
		/*check if it arg starts with = */
		node = begin_node(info->env, &info->argv[i][1], '=');
		if (node)
		{
			/*remove = and replace it with real data to avoid confusion*/
			stri_replce(&(info->argv[i]), _strdup(_strlocate(node->str, '=') + 1));
			continue;
		}
		/*ensure no other case except from above*/
		stri_replce(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * stri_replce - replace string
 * @old: old one
 * @new: new one
 * Return: 1 if replaced, 0 if not
 */

int stri_replce(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
