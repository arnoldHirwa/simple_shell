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

#define min(x, y) (((x) < (y)) ? (x) : (y))

typedef struct location
{
    DIR *dir;
    char *path;
    struct location *next;
} location;

extern char** environ;
int _execve(const char *file, char *const *argv, char *const *env);
size_t _getline(char **buf, size_t *len, FILE *source);
char *_strtok(char *str, char *sep);
void handle_signal(int signum);
void find_program(char *buf);
int _which(int ac, char **av);
char *_getenv(const char *name);
int _strcmp(const char *s1,const char *s2);
char *_strcat(char *dest, char *src);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
int _strlen(char *s);
void _printenv();
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strncat(char *dest, char *src, int n);
char *_strcpy(char *dest, char *src);
location* linked_dir();
void add_dir(location* link,char *path);
void _chdir(char *buf);

#endif /*ifndef MAIN_H*/
