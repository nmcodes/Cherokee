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

typedef struct      cherokee_response {
    Http_Version    version;
    Http_Status     status;
    Http_Header     *headers;
    void            *body;
    int             body_length;
    char            *raw;
}                   c_response;

void log_response(c_response *res);
int build_response(c_response *res);
c_response *new_response();

#endif
