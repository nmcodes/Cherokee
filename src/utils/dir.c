/*
** dir.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <stdio.h>

#include "dir.h"

c_dir *get_dir(char *path) {
    DIR *dir;
    struct dirent *entry;
    c_dir *cdir;
    c_dir_entry *last_entry;

    cdir = malloc(sizeof(c_dir));
    cdir->name = NULL;
    cdir->entries = NULL;
    if (!(dir = opendir(path)))
        return NULL;

    cdir->name = strdup(path);
    while ((entry = readdir(dir)) != NULL) {
        // if (entry->d_type == DT_DIR) {
        //     cdir->name = entry->d_name;
        // } else {
            c_dir_entry *centry;
            centry = malloc(sizeof(c_dir_entry));
            centry->name = entry->d_name;
            centry->next = NULL;

            if (cdir->entries == NULL) {
                cdir->entries = centry;
            } else {
                last_entry->next = centry;
            }
            last_entry = centry;
        // }
    }
    closedir(dir);
    return cdir;
}
