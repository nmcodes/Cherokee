/*
** config.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "config.h"
#include "../log/log.h"
#include "../inih/ini.h"


static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    c_config* pconfig = (c_config*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("config", "port")) {
        pconfig->port = atoi(value);
    } else if (MATCH("config", "loglevel")) {
        pconfig->loglevel = strdup(value);
    } else if (MATCH("config", "logfile")) {
        pconfig->logfile = strdup(value);
    } else if (MATCH("config", "rootpath")) {
        pconfig->rootpath = strdup(value);
    }  else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

int test_config() {
        c_config config;

    if (ini_parse("/tmp/config.ini", handler, &config) < 0) {
        printf("Can't load 'config.ini'\n");
        return 1;
    }
    printf("Config loaded from 'test.ini': port=%d, loglevel=%s, logfile=%s, rootpath=%s\n",
        config.port, config.loglevel, config.logfile, config.rootpath);
    return 0;
}

c_config *new_config() {
    c_config *config;

    config = malloc(sizeof(c_config));
    config->rootpath = "/usr/local/share/http";

    return config;
}


