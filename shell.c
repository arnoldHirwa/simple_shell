#include "main.h"

/**
 *main - Entry point
 *@ac: len of av
 *@av: number of params
 *Return: Always 0 (Success)
 */

int main(int ac, char **av)
{
	info_t info[] = {START_INFO};
	int fd = 2; /*FILE DESCRIPTOR*/

	if (ac == 2) /*when there is only one command and 1 arg*/
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1) /*CASE UNABLE TO OPEN A FILE*/
		{
			if (errno == EACCES) /*EACCESS: PERMISSION DENIED*/
				exit(126);
			if (errno == ENOENT) /* ENOENT: NO SUCH FILE OR DIRECTORY*/
			{
				_printstr(av[0]); /*PRINT THE FIRST ARGUMENT TO THE STANDARD ERROR*/
				_printstr(": 0: Can't open ");
				_printstr(av[1]); /*PRINT THE FILE YOU ARE UNABLE TO OPEN*/
				_putcharstdr('\n');
				_putcharstdr(-1); /*FLUSH THE BUFFER*/
				exit(127); /*EXIT WITH STATUS 127*/
			}
			return (EXIT_FAILURE); /*RETURN MACRO WHICH SHOWS THAT THE FUNCTION FAILED*/
		}
		info->fdread = fd; /*KEEP FILE DESCRIPTOR WHEN YOU ARE ABLE TO OPEN FILE*/
	}
	addenv_list(info); /*KEEP THE ENVIRONMENT VARIABLES IN INFO->ENV*/
	hist_rd(info); /*FOR CREATING A LIST OF HISTORY LINES*/
	iterate_sh(info, av); /*PASS ALL DATA AND ARGUMENTS TO iterate_sh FUNCTION*/
	return (EXIT_SUCCESS);
}
