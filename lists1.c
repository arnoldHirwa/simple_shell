#include "main.h"

/* $ */

/**
 * add_node - add node to strat list
 * @head: adrees of pint head node
 * @str: str field
 * @num: node index used by hist
 * Return: size of node
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - add node at the end
 * @head: adress of point head node
 * @str: field node str
 * @num: node index used by hist
 * Return: size of list
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t)); /*allocate mem. for node*/
	if (!new_node) /*return null if allocation fails*/
		return (NULL);
	/*fill the obtained memory with 0 to avoid character conflicts*/
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num; /*add number of characters of str*/
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str) /*if failed to create a pointer to a the string*/
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next) /*move untill you reach the end of the list*/
			node = node->next;
		node->next = new_node; /*add the new_node to the last node*/
	}
	else
		*head = new_node; /*if there wasn't any node, new_node will be the head*/
	return (new_node); /*return the last node of the list*/
}

/**
 * _putlist_str - print elem of linked list
 * @h: pointer first node
 * Return: size of list
 */

size_t _putlist_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		put_str(h->str ? h->str : "(nil)");
		put_str("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * remov_node - remove a node at a specific index
 * @head: adresse of pointer 1st node
 * @index: index of node deleted
 * Return: 1 (Success), 0 (Fail)
 */

int remov_node(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * list_cleaner - free all nodes
 * @head_ptr: add point head node
 * Return: void
 */

void list_cleaner(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
