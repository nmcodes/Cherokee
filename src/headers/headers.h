/*
** request.h for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __HEADERS_H__
#define __HEADERS_H__

#include <string.h>
#include <stdio.h>

typedef struct cherokee_request c_request;
typedef struct cherokee_response c_response;


typedef struct              c_Http_Header {
    char                    *key;
    char                    *value;
    struct c_Http_Header    *next;
}                           Http_Header;

#define CONTENT_TYPE_NOT_BINARY 0
#define CONTENT_TYPE_BINARY 1

typedef struct          c_Content_type {
    char                *type;
    char                *value;
    int                 is_binary;
}                       Content_Type;

#include "../request/request.h"
#include "../response/response.h"

void free_headers(Http_Header *headers);

void add_request_header(c_request *req, Http_Header *header);
void add_response_header(c_response *res, Http_Header *header);
Http_Header *find_header(Http_Header *h, const char *key);

Http_Header *new_date_header();
Http_Header *new_content_type_header(char *data_type);
Http_Header *new_content_length_header(int length);
Http_Header *new_server_header();

int is_binary_content_type(char *data_type);

#endif
