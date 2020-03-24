/*
** config.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "config.h"

c_config *new_config() {
    c_config *config;

    config = malloc(sizeof(c_config));
    config->root_path = "/usr/local/share/http";

    return config;
}
