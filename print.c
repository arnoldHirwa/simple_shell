#include "main.h"


/**
 * _printstr - prints a string
 * @str: pointer to string to print
 * Return: none
 */
void _printstr(char *str)
{
	write(1, str, _strlen(str));
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
