#include "main.h"

/**
 * _listleng - len of linked
 * @h: pointer 1st node
 * Return: size of list
 */

size_t _listleng(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_string - return arr string list str
 * @head: pointer 1st node
 * Return: arr of string
 */

char **list_string(list_t *head)
{
	list_t *node = head;
	size_t i = _listleng(head), j;
	char **strs, *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * pri_list - print elem of linked
 * @h: point 1st node
 * Return: size of node
 */

size_t pri_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		put_str(changenb(h->num, 10, 0));
		put_char(':');
		put_char(' ');
		put_str(h->str ? h->str : "(nil)");
		put_str("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * begin_node - return node start with specific alias name
 * @node: pointer 1st node
 * @name: string to match, first arg from main
 * @c: next char after prefix to much, separator in other words
 * Return: match node or null
 */

list_t *begin_node(list_t *node, char *name, char c)
{
	char *p = NULL;

	while (node) /*iterate through all aliases*/
	{
		p = start_with(node->str, name); /*get alias that start with the name*/
		if (p && ((c == -1) || (*p == c)))
			return (node); /*send the alias if found*/
		node = node->next;
	}
	return (NULL); /*if not found*/
}

/**
 * get_nodeid - get index of node
 * @head: point 1st head
 * @node: point to node
 * Return: index of node
 */

ssize_t get_nodeid(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
