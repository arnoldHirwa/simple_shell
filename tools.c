#include "main.h"

/**
 * interact - check if shell is interactive
 * @info: pointer to the struct contains info
 * Return: 1 (interactive), 0 if not
 */

int interact(info_t *info)
{
	/*isatty returns 0 if fd is non interactive/not from terminal*/
	/*info->fdread checks if fdread is either 0, 1, 2, which are standard values*/
	return (isatty(STDIN_FILENO) && info->fdread <= 2);
}

/**
 * delim_true - check if is delim
 * @c: char to check
 * @delim: delim string
 * Return: 1 (true), 0 if not
 */

int delim_true(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == c)
			return (1);
		delim++;
	}

	return (0);
}

/**
 * alphab_true - check if is alpha
 * @c: char to check
 * Return: 1 (true), 0 if not
 */

int alphab_true(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _atoint - convert string to int
 * @s: string to convert
 * Return: 0 if no number found, convert if any
 */

int _atoint(char *s)
{
	int sign = 1;
	unsigned int res = 0;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = (res * 10) + (*s - '0');
		s++;
	}
	return (sign * res);
}
