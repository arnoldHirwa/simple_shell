#include "main.h"

/**
 * _printenv - Print the environment variables
 */
void _printenv(void)
{
	int i = 0;

	while (environ[i])
	{
		_printstr(environ[i]);
		putchar('\n');
		i++;
	}
}
