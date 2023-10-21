#include "main.h"

/* $ */

/**
 * _strlen - return len of string
 * @s: the string counted
 * Return: len of string
 */

int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s++)
	{
		i++;
	}
	return (i);
}

/**
 * _strcmp - compare two strings
 * @s1: 1st string
 * @s2: 2nd string
 * Return: 0 if (s1 = 2), 1 if (s1 > s2), -1 if (s1 < s2)
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * start_with - check if name is the same as the real env.
 * @real_env: real env. value
 * @name: env - name to find
 * Return: addres of next character of haystack or NULL
 */

char *start_with(const char *real_env, const char *name)
{
	while (*name) /*iterate through the string until all characters are equal*/
	{
		if (*name++ != *real_env++)
			return (NULL);
	}
	return ((char *)real_env);/*return the real string if successful*/
}

/**
 * _strncat - concat twi string
 * @dest: destination buffer
 * @src: source buffer
 * Return: pointer to desti buffer
 */

char *_strncat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;

	*dest = *src;
	return (ret);
}
