#include "main.h"

/**
 * hist_get - get the data from the home environment
 * and concatenate the result with ".simple_shell_history"
 * @info: struct
 * Return: history file
 */

char *hist_get(info_t *info)
{
	char *buf, *hom;

    /*get env-value which start with HOME= characters*/
	hom = _getenv(info, "HOME=");
	if (!hom) /*if home invironment is not found, return null*/
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(hom) + _strlen(HIST_FILE) + 2));
	if (!buf) /*if unable to allocate memory, return null*/
		return (NULL);
	buf[0] = 0; /*to avoid conflicting characters in memory space*/
	/*concatenate the home environment with / ".simple_shell_history"*/
	_strcpy(buf, hom);
	_strncat(buf, "/");
	_strncat(buf, HIST_FILE);
	return (buf); /*return the concatenated string*/
}

/**
 * hist_wrt - create file append exiting file
 * @info: struct
 * Return: 1 (Success), -1 (Fail)
 */

int hist_wrt(info_t *info)
{
	ssize_t fd;
	char *filename = hist_get(info);
	list_t *node = NULL;

	if (!filename)/*if unable to open history*/
		return (-1);
	/*open the history file with needed permision and add data to it*/
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(filename); /*to avoid memory leaks*/
	if (fd == -1) /*if unable to create, read, and truncate data to file*/
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_printsfd(node->str, fd);
		_putfd('\n', fd); /*add a new line to mark termination*/
	}
	_putfd(-1, fd); /*flush the buffer*/
	close(fd); /*close file descriptor*/
	return (1);
}

/**
 * hist_rd - read hist file
 * @info: struct
 * Return: sit when (Success), 0 (Fail)
 */

int hist_rd(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = hist_get(info);

	if (!filename) /*No combined string of home-env and ".simple_shell_history"*/
		return (0);
	fd = open(filename, O_RDONLY); /*open the path to home-history*/
	free(filename); /*release filename to avoid memory leaks*/
	if (fd == -1) /*if unable to open the file, return 0*/
		return (0);
	/*fstat obtain permission of file shown by a specific path*/
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2) /*if file size < 2, this is not a typical file*/
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1)); /*memory of obtained file*/
	if (!buffer) /*return null on error*/
		return (0);
	/*while reading the history_file is automatically created*/
	rdlen = read(fd, buffer, fsize); /*read file characters to buffer*/
	buffer[fsize] = 0; /*to avoid conflicting memory issues*/
	if (rdlen <= 0) /*if unable to read, free buffer and return 0*/
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < fsize; i++) /*iterate through all characters of buf*/
		if (buffer[i] == '\n') /*after reaching to the end of line*/
		{
			buffer[i] = 0; /*to avoid conflicts in memory*/
			hist_maker(info, buffer + last, linecount++);
			last = i + 1; /*for incrementing memory location of buf*/
		}
	if (last != i) /*for a buf which doesn't end with \n*/
		hist_maker(info, buffer + last, linecount++);
	free(buffer); /*release the buffer*/
	info->counthist = linecount; /*add number of lines of history file*/
	while (info->counthist-- >= 4096) /*if exceeds max_lines*/
		remov_node(&(info->history), 0);/*remove the first node*/
	hist_align(info);
	return (info->counthist);
}

/**
 * hist_maker - create a linked list of history
 * @info: struct
 * @buf: buffer
 * @linecount: counthist
 * Return: 0 (Success)
 */

int hist_maker(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history; /*grab the head node*/
	/*add the read_string node to the end of the list*/
	add_node_end(&node, buf, linecount);

	if (!info->history) /*the first string will be the first node*/
		info->history = node;
	return (0);
}

/**
 * hist_align - aligns the number of node
 * @info: struct of nodes of history lines
 * Return: number of history lines
 */

int hist_align(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++; /*align all nodes starting from 0*/
		node = node->next;
	}
	return (info->counthist = i);
}
