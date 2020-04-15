/*
** custom.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "custom.h"
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

c_router *new_router() {
    c_router *router;

    router = malloc(sizeof(c_router));
    router->path = NULL;
    router->has_get = 0;
    router->has_post = 0;
    router->has_put = 0;
    router->has_delete = 0;
    router->next = NULL;
    return router;
}

void listdir(const char *name, int depth, c_router *r)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

            if (depth == 1) {
                if (r->path == NULL) {
                    r->path = malloc(strlen(entry->d_name) + 2);
                    sprintf(r->path, "/%s", entry->d_name);
                    listdir(path, depth + 1, r);
                } else {
                    r->next = new_router();
                    r->next->path = malloc(strlen(entry->d_name) + 2);
                    sprintf(r->next->path, "/%s", entry->d_name);
                    listdir(path, depth + 1, r->next);
                }
            }
        } else {
            if (r->path != NULL) {
                if (strcmp(entry->d_name, "get.py") == 0) {
                    r->has_get = 1;
                }
                if (strcmp(entry->d_name, "post.py") == 0) {
                    r->has_post = 1;
                }
                if (strcmp(entry->d_name, "put.py") == 0) {
                    r->has_put = 1;
                }
                if (strcmp(entry->d_name, "delete.py") == 0) {
                    r->has_delete = 1;
                }
            }
        }
    }
    closedir(dir);
}

c_router *get_router_from_url(char *url) {
    c_router *r;

    if (url == NULL)
        return NULL

    r = config->router;
    while (r != NULL) {
        if (strcmp(url, r->path) == 0) {
            return r;
        }
        r = r->next;
    }
    return NULL;
}

c_router *get_custom_router(c_config *config) {
    c_router *r;
    r = new_router();

    listdir(config->customdir, 1, r);

    printf("r->path : %s\n", r->path);
    printf("r->has_get : %d\n", r->has_get);
    printf("r->has_post : %d\n", r->has_post);
    printf("r->next->path : %s\n", r->next->path);
    printf("r->has_get : %d\n", r->next->has_get);
    printf("r->has_post : %d\n", r->next->has_post);
    return r;
}
