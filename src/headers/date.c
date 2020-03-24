/*
** date.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <time.h>

#include "headers.h"

Http_Header *new_date_header() {
    Http_Header *h;
    time_t timestamp;

    h = malloc(sizeof(Http_Header));
    h->next = NULL;
    h->key = "Date";
    h->value = malloc(256 * sizeof(char));

    timestamp = time(NULL);
    strftime(h->value, sizeof(h->value), "%a, %d %b %Y %X", localtime(&timestamp));

    return h;
}
