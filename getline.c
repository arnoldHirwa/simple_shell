#include "main.h"

#define BUFFSIZE 1024

/**
* _getline - Read a line from a file
* @buf: A pointer to the buffer where the line is stored
* @len: A pointer to the length of the buffer
* @source: The file to read from
*
* Return: The number of characters read, -1 on failure
*/
size_t _getline(char **buf, size_t *len, FILE *source)
{
	int read_res;
	int n = 0;
	char buff[1];

	if (source == NULL)
		return (_perro("Invalid file"));

	while (1)
	{
		read_res = read(STDIN_FILENO, &buff, 1);

		if (read_res == -1)
			return (_perro("read_res"));

		if (n > (int)(*len) - 1)
		{
			*len += BUFFSIZE;
			*buf = _realloc(*buf, *len - BUFFSIZE, *len);
			if (*buf == NULL)
				return (_perro("realloc"));
		}

		if (*buff == '\n')
		{
			(*buf)[n] = '\0';
			break;
		}
		else
		{
			(*buf)[n] = buff[0];
			n++;
		}
	}
	*len = n;
	return (n);
}
