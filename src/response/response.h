/*
** response.h for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/


#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <stdlib.h>

#include "../http.h"
#include "../headers/headers.h"


typedef struct      cherokee_Http_Status {
    int             code;
    char            *hint;
}                   Http_Status;

static const Http_Status STATUS_200_OK = { 200, "OK" };
static const Http_Status STATUS_404_NOT_FOUND = { 404, "Not Found" };

typedef struct  Cherokee_response_body {
    void        *content;
    int         length;
    int         is_binary;
}               c_response_body;

typedef struct      cherokee_response {
    Http_Version    version;
    Http_Status     status;
    Http_Header     *headers;
    c_response_body *body;
    char            *raw;
}                   c_response;

void log_response(c_response *res);
int build_response(c_response *res);

c_response *new_response();
void free_response(c_response *res);

#endif
