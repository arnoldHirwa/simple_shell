#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define HIST_FILE ".simple_shell_history" /*needed to avoid long line*/

extern char **environ;

/**
 * struct liststr - linked list
 * @num: field number
 * @str: string
 * @next: pointer to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains arguments to pass into a function,
 * @arg: string generate from getline contains arguments
 * @argv: an array of string generate from arg
 * @path: string path for the current command
 * @argc: argument count
 * @count_line: error count
 * @num_err: error code for exit
 * @flag_lncount: count line of inputs
 * @namefile: filename
 * @env: linked list for copu of env
 * @environ: custom modified copy of env
 * @history: history node
 * @alias: list that keeps aliases
 * @changed_env: if env was changed
 * @status: return status of the list exec'd command
 * @buf_cmd: address point to buf_cmd
 * @buf_cmd_type: cmd_type ||,, &&, ;
 * @fdread: fd from which read line input
 * @counthist: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int count_line;
	int num_err;
	int flag_lncount;
	char *namefile;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int changed_env;
	int status;
	char **buf_cmd;
	int buf_cmd_type;
	int fdread;
	int counthist;
} info_t;

/*This is the macro which shows all values of into_t structure*/
#define START_INFO                                                         \
	{                                                                     \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, \
			NULL, 0, 0, 0                                                 \
	}

/**
 *struct inbuilt - contains inbuilt string
 *@type: inbuilt command flag
 *@func: function
 */

typedef struct inbuilt
{
	char *type;
	int (*func)(info_t *);
} inbuilt_table;

int iterate_sh(info_t *, char **);
int built_find(info_t *);

void command_find(info_t *);
void command_forkd(info_t *);
int command(info_t *, char *);

char *char_dupl(char *, int, int);
char *path_findh(info_t *, char *, char *);

void _printstr(char *);
int _putcharstdr(char);
int _putfd(char, int);
int _printsfd(char *, int);

int _strlen(char *);
int _strcmp(char *, char *);
char *start_with(const char *, const char *);
char *_strncat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void put_str(char *);
int put_char(char);

char *_strncpy(char *, char *, int);
char *_strnconcat(char *, char *, int);
char *_strlocate(char *, char);

char **_strword_a(char *, char *);
char **_strword_b(char *, char);

char *_memset(char *, char, unsigned int);
void _freestrn(char **);
void *_memrealloc(void *, unsigned int, unsigned int);
int pointer_free(void **);

int interact(info_t *);
int delim_true(char, char *);
int alphab_true(int);
int _atoint(char *);

int int_err(char *);
void _errorput(info_t *, char *);
int _decimalput(int, int);
char *changenb(long int, int, int);
void romove_com(char *);

int exit_all(info_t *);
int _chdi(info_t *);
int find_help(info_t *);
int find_histor(info_t *);
int find_alia(info_t *);
int _findenv(info_t *);

int _unsetalia(info_t *, char *);
int _setalia(info_t *, char *);
int _putalia(list_t *);

ssize_t _getinput(info_t *);
int _getline(info_t *, char **, size_t *);
void sigint_handler(int);

void _dataclean(info_t *);
void data_set(info_t *, char **);
void data_free(info_t *, int);

char *_getenv(info_t *, const char *);
int _setenviro(info_t *);
int un_setenviro(info_t *);
int addenv_list(info_t *);
char **env_return(info_t *);
int _makenv(info_t *, char *, char *);
int _delenv(info_t *, char *);

char *hist_get(info_t *);
int hist_wrt(info_t *);
int hist_rd(info_t *);
int hist_maker(info_t *, char *, int);
int hist_align(info_t *);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t _putlist_str(const list_t *);
int remov_node(list_t **, unsigned int);
void list_cleaner(list_t **);

size_t _listleng(const list_t *);
char **list_string(list_t *);
size_t pri_list(const list_t *);
list_t *begin_node(list_t *, char *, char);
ssize_t get_nodeid(list_t *, list_t *);

int serie(info_t *, char *, size_t *);
void check_serie(info_t *, char *, size_t *, size_t, size_t);
int _replacealia(info_t *);
int _replacevar(info_t *);
int stri_replce(char **, char *);

#endif
