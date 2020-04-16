/*
** headers.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "./headers.h"
#include "../log/log.h"
#include <stdlib.h>
#include <string.h>

void add_request_header(c_request *req, Http_Header *header) {
    Http_Header *last_header;

    if (req->headers == NULL) {
        req->headers = header;
    } else {
        last_header = req->headers;
        while (last_header->next != NULL) {
            last_header = last_header->next;
        }
        last_header->next = header;
    }
}

void add_response_header(c_response *res, Http_Header *header) {
    Http_Header *last_header;

    if (res->headers == NULL) {
        res->headers = header;
    } else {
        last_header = res->headers;
        while (last_header->next != NULL) {
            last_header = last_header->next;
        }
        last_header->next = header;
    }
}

void free_headers(Http_Header *headers) {
    Http_Header *i, *h;
    if (headers == NULL) {
        return;
    }
    i = headers;
    while (i != NULL) {
        h = i;
        i = i->next;
        free(h);
    }
}

Http_Header *find_header(Http_Header *h, const char *key) {
    if (h == NULL)
        return NULL;
    while (h->next != NULL && strcmp(h->key, key) != 0) {
        h = h->next;
    }

    if (strcmp(h->key, key) == 0)
        return h;

    return NULL;
}

