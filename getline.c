#include "main.h"

/**
 * _input_buf - buffer serieed
 * @info: struct of params
 * @buffer: adress of buffer
 * @len: aress of len
 * Return: readed byte
 */

ssize_t _input_buf(info_t *info, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /*when the length of read data is 0*/
	{
		free(*buffer); /*release buffer*/
		*buffer = NULL;
		signal(SIGINT, sigint_handler); /*for handling EOF*/
		r = _getline(info, buffer, &len_p); /*read data and store them to buffer*/
		if (r > 0) /*when we have successfully read data to the buf*/
		{
			/*if we reached to the new line, terminate string with a new line char*/
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--; /*update the real length of read chars from getline function*/
			}
			info->flag_lncount = 1; /*show that you have read the line*/
			romove_com(*buffer); /*remove comment from the buffe. remain with command*/
			hist_maker(info, *buffer, info->counthist++); /*hist + new command*/
			{
				*len = r; /*update the len with read chars*/
				info->buf_cmd = buffer; /*update the command to execute with read buffer*/
			}
		}
	}
	return (r); /*return len of read chars*/
}

/**
 * _getinput - gets line - the new line
 * @info: struct of params
 * Return: readed byte
 */

ssize_t _getinput(info_t *info)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buffer_p = &(info->arg), *p;

	put_char(-1); /*flush the buffer to stdout before proceeding*/
	/*getline and add command to data struct*/
	r = _input_buf(info, &buffer, &len);
	if (r == -1) /*return -1 if getting command was unsuccessful*/
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i; /*assign p to the command in buffer*/
		check_serie(info, buffer, &j, i, len); /*check if there is && ||*/
		while (j < len) /*when there is no || or && command*/
		{
			/*check the presence of operators (|| && ..)*/
			if (serie(info, buffer, &j)) /*it will normally return 0 if there is one*/
				break; /*continue fx*/
			j++;
		}

		i = j + 1; /*start reading another command from updated position*/
		if (i >= len) /*return to normal mode is i exceeded len of buf*/
		{
			i = len = 0; /*in this there might be other command to read*/
			info->buf_cmd_type = 0;
		}
		*buffer_p = p; /*update arguments with the obtained buffer*/
		return (_strlen(p)); /*return length of buffer*/
	}
	*buffer_p = buffer; /*if is in beggining, the arguments will be the buffer*/
	return (r);
}

/**
 * _read_buf - read a buffer
 * @info: the main data struct
 * @buf: where data will be stored
 * @i: size of data to read
 * Return: r
 */

ssize_t _read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i) /*return zero if size of data to read > 0*/
		return (0);
	r = read(info->fdread, buf, 1024);
	if (r >= 0)
		*i = r; /*update the size of i after reading r data*/
	return (r); /*return the actual data read*/
}

/**
 * _getline - find a line to be executed
 * @info: struct of params
 * @ptr: adress of buffer
 * @lenght: size
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *lenght)
{
	static char buffer[1024];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL;
	char *new_p = NULL, *c;

	p = *ptr; /*copy address of destinatio_buffer to p*/
	if (p && lenght)
		s = *lenght; /*if we have a buffer and size > 0, cpy size*/
	if (i == len)
		i = len = 0; /*initialize i and len to 0 if starting the function*/

	r = _read_buf(info, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1); /*return zero if len = 0 or reading has failed*/
	c = _strlocate(buffer + i, '\n'); /*first occurence of new line in buffer*/
	/*if c exists, k = 1 + (c - buf): k = len of line from start to end of buf*/
	/* else if no end of line, k = initial size of read data i.e: len*/
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	/*reallocate buffer from old size to include read size k or new line char*/
	new_p = _memrealloc(p, s, s ? s + k : k + 1);
	if (!new_p) /*if reallocatin fails, free p pointer and return -1*/
		return (p ? free(p), -1 : -1);
	if (s) /*if size of buf != 0*/
		_strnconcat(new_p, buffer + i, k - i); /*fill new memory with new buff*/
	else /*length of buf = 0*/
		_strncpy(new_p, buffer + i, k - i + 1); /*cpy new buffer to new memo*/

	s += k - i; /*update the length of read chars*/
	i = k; /*increment the current initial chars*/
	p = new_p; /*restore p to new_p address*/
	if (lenght)
		*lenght = s; /*update the size of buf*/
	*ptr = p; /*update the received pointer*/
	return (s); /*return size of read chars*/
}

/**
 * sigint_handler - handle the EOF signal
 * @sig: signal number
 * Return: void
 */

void sigint_handler(__attribute__((unused)) int sig)
{
	put_str("\n");
	put_str("$: "); /*add a new line and a prompt to receive new command*/
	put_char(-1);
}
