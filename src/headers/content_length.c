/*
** content_length.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "headers.h"

Http_Header *new_content_length_header(int length) {
    Http_Header *h;

    h = malloc(sizeof(Http_Header));
    h->next = NULL;
    h->value = malloc(10);
    h->key = "Content-Length";
    sprintf(h->value, "%d", length);

    printf("Content-Length header builded : %s: %s\n", h->key, h->value);
    return h;
}
