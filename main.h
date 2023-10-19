#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/dir.h>
#include <errno.h>
#include <stdbool.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define MAX_NUM_TOKENS 10

/**
* struct location - represents a directory location
* @dir: pointer to a directory
* @path: path to the directory
* @next: pointer to the next location in a linked list
*/
typedef struct location
{
	DIR *dir;
	char *path;
	struct location *next;
} location;

#define MAX_ALIASES 50
extern char **environ;
int _execve(const char *file, char *const *argv, char *const *env);
size_t _getline(char **buf, size_t *len, FILE *source);
char *_strtok(char *str, char *sep);
void handle_signal(int signum);
void find_program(char *buf);
int _which(int ac, char **av);
char *_getenv(const char *name);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, char *src);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
int _strlen(char *s);
void _printenv(void);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strncat(char *dest, char *src, int n);
char *_strcpy(char *dest, char *src);
location *linked_dir();
void add_dir(location *link, char *path);
void _chdir(char *buf);
int exec_command(char *duplicate);
void _operator(bool doIt, char *string, bool start, bool wasOr);
char *_perror(char *c);
char *_strdup(char *str);
char *_strchr(char *s, char c);
int _perro(char *c);
char *_strstr(char *haystack, char *needle);
int _bin(char *path, char **p, char *duplicate);
int find_function(char *token, char *original);

#endif /* ifndef MAIN_H */
