/*
** request.h for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __HEADERS_H__
#define __HEADERS_H__

typedef struct cherokee_request c_request;

typedef struct              c_Http_Header {
    char                    *key;
    char                    *value;
    struct c_Http_Header    *next;
}                           Http_Header;

#include "../request.h"

void add_header(c_request *req, Http_Header *header);
Http_Header *find_header(c_request *req, const char *key);

#endif
