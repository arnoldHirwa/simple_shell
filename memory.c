#include "main.h"

/**
 * _memset - fill memory with specific character
 * @s: pointer to memory area
 * @b: character to fill
 * @n: amount of bytes field
 * Return: pointer to the start of memory location
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;

	return (s);
}

/**
 * _freestrn - free string of strings
 * @s: string of strings
 * Return: void
 */

void _freestrn(char **s)
{
	char **a = s;

	if (!s)
		return;

	while (*s)
		free(*s++);

	free(a);
}

/**
 * _memrealloc - reallocation of a specific memo
 * @ptr: pointer to last memory
 * @old_size: size last memory
 * @new_size: size of new memory
 * Return: pointer
 */

void *_memrealloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (p);
}

/**
 * pointer_free - frees pointer and put null to the adresse
 * @ptr: adresse of pointer
 * Return: 1 (Success), 0 (FAIL)
 */

int pointer_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
