/*
** file.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __FILE_H__
#define __FILE_H__

#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char *get_file_path(char *root_path, char *url);
char *get_file_extension(const char *filename);
void *read_file(const char *file_path, int *size);

#endif
