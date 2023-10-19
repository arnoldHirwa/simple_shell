#include "main.h"

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	size_t len = 0;
	int n;
	char *buf;

	signal(SIGINT, handle_signal);

	while (1)
	{
		printf("{^_^} $ ");
		fflush(stdout);
		buf = malloc(1024);
		n = _getline(&buf, &len, stdin);
		if (n > 0)
		{
			find_program(buf);
			free(buf);
		}
	}
	return (0);
}
