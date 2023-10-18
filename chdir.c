#include "main.h"


void _chdir(char *buf)
{
    char *sep = "\n ";
    char *path = _strtok(buf, sep), cwdir[1024] = "";
    static int num = 0;
    int changed;
    static location *dirs;
    location *current = NULL;

    path = _strtok(NULL, sep);
    if (num == 0)
    {
        dirs = malloc(sizeof(location));
        dirs = linked_dir();
        num++;
    }
    current = dirs;
    while (current != NULL)
    {
        current = current->next;
    }
    if (path == NULL)
    {
        if (strcmp(_getenv("PWD"), _getenv("HOME")) == 0)
            return;
        _setenv("PWD", _getenv("HOME"), 1);
        changed = chdir(_getenv("HOME"));
        if (changed == -1)
        {
            perror("bash cd:");
            return;
        }
        getcwd(cwdir, 1024);
        add_dir(dirs, cwdir);
    } else if (_strcmp(path, "-") != 0)
    {
        while (current != NULL)
        {
            current = current->next;
        }
        _strcat(cwdir, _getenv("PWD"));
        _strcat(cwdir, "/");
        _strcat(cwdir, path);
        current = dirs; 

        changed = chdir(cwdir);
        if (changed == -1)
        {
            perror("bash: cd");
            return;
        }
       
        _setenv("PWD", getcwd(cwdir, 1024), 1);
      
        add_dir(dirs, cwdir);
    } else
    {
        current = dirs;
        while(current->next->next != NULL) 
        {
            current = current->next;
        }
        _setenv("PWD", current->path, 1);
        add_dir(dirs, _getenv("PWD"));
        changed = chdir(current->path);
        if (changed == -1)
        {
            perror("bash: cd");
            return;
        }
    }
}
