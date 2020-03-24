/*
** date.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <time.h>

#include "headers.h"

Http_Header *new_server_header() {
    Http_Header *h;

    h = malloc(sizeof(Http_Header));
    h->next = NULL;
    h->key = "Server";
    h->value = "myCherokee";
    return h;
}
