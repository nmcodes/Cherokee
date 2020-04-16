/*
** dir.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __DIR_H__
#define __DIR_H__

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

typedef struct                  cherokee_dir_entry {
    char                        *name;
    struct cherokee_dir_entry   *next;
}                               c_dir_entry;

typedef struct  cherokee_dir {
    char        *name;
    c_dir_entry *entries;
}               c_dir;

c_dir *get_dir(char *path);

#endif


