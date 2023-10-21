#include "main.h"

/**
 * _strncpy - cpys a string
 * @dest: the destination string to copied
 * @src: source string
 * @n: amount char copied
 * Return: concat string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, k;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		k = i;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 * _strnconcat - add 2 strings together
 * @dest: 1st string
 * @src: 2nd string
 * @n: amount of bytes used
 * Return: concat string
 */

char *_strnconcat(char *dest, char *src, int n)
{
	int i, k;
	char *s = dest;

	i = 0;
	k = 0;
	while (dest[i] != '\0')
		i++;
	while (src[k] != '\0' && k < n)
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	if (k < n)
		dest[i] = '\0';

	return (s);
}

/**
 * _strlocate - this finds the first occurence of c
 * c if found in string s
 * @s: string to pass through
 * @c: char to look for
 * Return: pointer to the first occurence of c in s
 */

char *_strlocate(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
