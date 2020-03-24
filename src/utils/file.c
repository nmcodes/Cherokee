/*
** file.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <stdio.h>

#include "file.h"

char *get_file_path(char *root_path, char *url) {
    char *file_path;

    file_path = malloc(strlen(root_path) + strlen(url) + 1);
    strcat(file_path, root_path);
    strcat(file_path, url);

    return file_path;
}

char *get_file_extension(const char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void *read_file(const char *file_path, int *size) {
    char *buf;
    FILE *fd;

    fd = fopen(file_path,"rb");
    fseek(fd, 0, SEEK_END); //go to end
    *size = ftell(fd); //get position at end (length)
    fseek(fd, 0, SEEK_SET); //go to beg.
    buf = (char *)malloc(*size); //malloc buffer
    fread(buf, *size, 1, fd); //read into buffer
    fclose(fd);

    printf("READ DATA FROM FILE : \n");
    int i =0;
    while (i < *size) {
        printf("%u ", buf[i]);
        i++;
    }
    printf("\n");

    return buf;
}
