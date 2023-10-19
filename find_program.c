#include "main.h"

/**
* find_program - Split and process a command buffer
* @buf: The command buffer to process
*/
void find_program(char *buf)
{
	char *tok, *dup;
	char **arr;
	int k, n;

	arr = malloc(strlen(buf) + 1);
	if (arr == NULL)
	{
		perror("Malloc arr");
		return;
	}
	dup = _strdup(buf);
	if (dup == NULL)
	{
		perror("strdup dup");
		free(arr);
		return;
	}
	tok = _strtok(dup, ";");
	if (tok == NULL)
	{
		free(dup);
		free(arr);
		perror("strtok tok");
		return;
	}
	arr[0] = tok;
	for (k = 1; (tok = _strtok(NULL, ";")) != NULL; k++)
	{
		arr[k] = tok;
	}
	for (n = 0; n < k; n++)
	{
		_operator(true, arr[n], true, false);
	}
	free(arr);
}
