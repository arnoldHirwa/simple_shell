#include "main.h"

/* $ */

/**
 * int_err - convert string to int
 * @s: string to be converted
 * Return: 0 if no num in the string, -1 (Error), num if true
 */

int int_err(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * _errorput - print error msg
 * @info: struct contains params & return info
 * @estr: string contains specific error
 * Return: 0 if no num in the string, -1 (Error), num if true
 */

void _errorput(info_t *info, char *estr)
{
	_printstr(info->namefile);
	_printstr(": ");
	_decimalput(info->count_line, STDERR_FILENO);
	_printstr(": ");
	_printstr(info->argv[0]);
	put_str(": ");
	_printstr(estr);
}

/**
 * _decimalput - print decimal number base 10
 * @input: input
 * @fd: fd to write to
 * Return: num if char printed
 */

int _decimalput(int input, int fd)
{
	int (*_put_char)(char) = put_char;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		_put_char = _putcharstdr;
	if (input < 0)
	{
		_abs_ = -input;
		_put_char('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			_put_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	_put_char('0' + current);
	count++;

	return (count);
}

/**
 * changenb - convert a specific number in a specific base
 * @num: number
 * @base: base
 * @flags: argument
 * Return: string
 */

char *changenb(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0, *ptr;
	unsigned long n = num;

	if (!(flags & 2) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arr = flags & 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * romove_com - romove comment from the buf by replacing # with \o
 * @buf: adress of string to modify
 * Return: void
 */

void romove_com(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		/*when there is # and previous char is empty char not at the beginning*/
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
