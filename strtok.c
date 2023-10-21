#include "main.h"

/* $ */

/**
 * **_strword_a - split string into words, delim are ignored
 * @str: input string
 * @d: delim string
 * Return: pointer to arr of string, or NULL if (FAIL)
 */

char **_strword_a(char *str, char *d)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!delim_true(str[i], d) && (delim_true(str[i + 1], d) || !str[i + 1]))
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (delim_true(str[i], d))
			i++;
		k = 0;
		while (!delim_true(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];

		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **_strword_b - split a string into words
 * @str: input string
 * @d: delim
 * Return: pointer to arr of string, or NULL (FAIL)
 */

char **_strword_b(char *str, char d)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) ||
			str[i + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;

		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 *find_help - display help
 *@info: struct for potential arguments
 *Return: 0 (Success)
 */

int find_help(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	put_str("help call work, function net yet implemented \n");
	if (0)
		put_str(*arg_arr);
	return (0);
}
