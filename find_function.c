#include "main.h"

/**
 * iterate_sh - allows shell to function continuously
 * @info: A struct which contains all data we need
 * @av: all arguments from main
 * Return: 0 (Success), 1 (Error)
 */

int iterate_sh(info_t *info, char **av)
{
	ssize_t r = 0;
	int inbuilt_ret = 0;

	while (r != -1 && inbuilt_ret != -2)
	{
		_dataclean(info); /*restart argc, argv, arg, and path to falsy values*/
		if (interact(info))
			put_str("$: "); /*print the prompt if we are in interactive mode*/
		_putcharstdr(-1); /*flush the buffer to ensure the prompt is printed*/
		r = _getinput(info); /*get command and update the args with obtained buf*/
		if (r != -1) /*if it doesn't fail*/
		{
			data_set(info, av); /*ensure argv is readable by shell*/
			inbuilt_ret = built_find(info); /*find specific buil in function*/
			if (inbuilt_ret == -1) /*-1 is when inbuilt is not found*/
				command_find(info);
		}
		else if (interact(info)) /*if we are in interactive mode after failure*/
		{
			put_char('\n'); /*add new line*/
		}
		data_free(info, 0); /*release the struct to avoid memory leaks*/
	}
	hist_wrt(info); /*write the current state in history file*/
	data_free(info, 1); /*release the struct to avoid memory leaks*/
	if (!interact(info) && info->status)
		exit(info->status); /*exit if we are not in interactive mode*/
	if (inbuilt_ret == -2) /*-2 is for exit inbuilt*/
	{
		if (info->num_err == -1)
			exit(info->status); /*if there was an error, exit with current status*/
		exit(info->num_err); /*otherwise exit with the current error*/
	}
	return (inbuilt_ret);
}

/**
 * built_find - find inbuilt command
 * @info: params & return info
 * Return: -1 if not found, 0 if execute success
 * 1 if found and execute not success
 * -2 if exit
 */

int built_find(info_t *info)
{
	int i, built_in_ret = -1;
	inbuilt_table inbuilttbl[] = {
		{"exit", exit_all},
		{"env", _findenv},
		{"help", find_help},
		{"history", find_histor},
		{"setenv", _setenviro},
		{"unsetenv", un_setenviro},
		{"cd", _chdi},
		{"alias", find_alia},
		{NULL, NULL}};

	/*iterate through all built ins*/
	for (i = 0; inbuilttbl[i].type; i++)
	{
		if (_strcmp(info->argv[0], inbuilttbl[i].type) == 0)
		{
			/*if one is found, call that particular function*/
			info->count_line++; /*increment error count*/
			built_in_ret = inbuilttbl[i].func(info);
			break;
		}
	}
	return (built_in_ret);
}
