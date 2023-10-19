#include "main.h"

/**
* _strtok - custom string tokenizer
* @str: the string to tokenize
* @sep: the separator characters
*
* Return: a pointer to the next token in the string,
* or NULL if there are no more tokens
*/
char *_strtok(char *str, char *sep)
{
	static char *full_str, *token;
	static int i;
	int initial_i = 0, j, k;

	if (str == NULL)
		initial_i = i;
	else
	{
		i = 0;
		full_str = malloc(strlen(str) + 1);
		if (full_str == NULL)
			return (_perror("malloc full_str or string"));
		_strcpy(full_str, str);
	}
	for (; (full_str[i] != '\0') || (i == (int)strlen(full_str)); i++)
	{
		for (j = 0; (sep[j] != '\0') || (i == (int)strlen(full_str)); j++)
		{
			if (full_str[i] == sep[j])
			{
				if (i == initial_i)
				{
					initial_i++;
					break;
				}
				k = i - initial_i;
				token = malloc(k);
				if (token == NULL)
					return (_perror("malloc token"));
				for (j = 0; j < k; j++, initial_i++)
					token[j] = full_str[initial_i];
				token[j] = '\0';

				if (i++ == k)
					_strcpy(str, token);
				return (token);
			}
		}
	}
	return (NULL);
}

/**
 * _perror - Print an error message and return NULL
 * @c: The error message to print
 *
 * This function prints an error message using perror() and returns NULL.
 *
 * Return: Always returns NULL.
 */
char *_perror(char *c)
{
	perror(c);
	return (NULL);
}
