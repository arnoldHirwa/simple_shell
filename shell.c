#include "main.h"

/**
* main - Entry point
*
* Return: Always 0 (Success)
*/
int main(void)
{
	size_t len = 0;
	char *buf = NULL;
	int n;
	int interactive = isatty(STDIN_FILENO);

	signal(SIGINT, handle_signal);

	while (1)
	{
		if (interactive)
		{
			_printstr("$ ");
			fflush(stdout);
		}

		n = getline(&buf, &len, stdin);

		if (n == -1)
		{
			free(buf);
			break;
		}

		if (n > 0)
		{
			exec_command(buf);
		}

		free(buf);
		buf = NULL;
	}

	return (0);
}
