#include "main.h"

/**
 * _printstr - prints input string
 * @str: string printed
 * Return: void
 */

void _printstr(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putcharstdr(str[i]);
		i++;
	}
}

/**
 * _putcharstdr - write char c to stderr
 * @c: char to print
 * Return: 1 (Success), -1 (Fail)
 */

int _putcharstdr(char c)
{
	static int i;
	static char buffer[1024];

	if (c == -1 || i >= 1024)
	{
		write(2, buffer, i); /*write chars to std. error*/
		i = 0;
	}
	if (c != -1)
		buffer[i++] = c;

	return (1);
}

/**
 * _putfd - write char c to a given file descriptor
 * @c: char to print
 * @fd: fd to write
 * Return: 1 (Success), -1 (Fail)
 */

int _putfd(char c, int fd)
{
	static int i;
	static char buffer[1024];

	/*if we haven't reached the buf limit and not going to flush*/
	if (c == -1 || i >= 1024)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (c != -1) /*continue to keep data in buf before flushing*/
		buffer[i++] = c;

	return (1);
}

/**
 * _printsfd - print input string in a given fd
 * @str: string to print
 * @fd: fd to write
 * Return: number of char
 */

int _printsfd(char *str, int fd)
{
	int k = 0;

	if (!str)
		return (0);

	while (*str) /*write all string in the file as you count*/
		k += _putfd(*str++, fd);

	return (k); /*return read characters*/
}
