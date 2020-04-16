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

<<<<<<< HEAD
void free_header(Http_Header *h) {
    if (h == NULL) {
        return;
    }
    if (h->key != NULL)
        free(h->key);
    if (h->value != NULL)
        free(h->value);
}

void free_headers(Http_Header *headers) {
    Http_Header *i, *h;

=======
void free_headers(Http_Header *headers) {
    Http_Header *i, *h;
    if (headers == NULL) {
        return;
    }
>>>>>>> edabd87ad8d559e490c70bd4306b9dcf9178e58f
    i = headers;
    while (i != NULL) {
        h = i;
        i = i->next;
<<<<<<< HEAD
        free_header(h);
    }
    free_header(h);
=======
        free(h);
    }
>>>>>>> edabd87ad8d559e490c70bd4306b9dcf9178e58f
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
