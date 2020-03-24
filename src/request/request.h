/*
** request.h for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "../headers/headers.h"
#include "../http.h"

typedef struct cherokee_response c_response;

typedef struct      cherokee_request {
    Http_Method     method;
    Http_Version    version;
    char            *url;
    Http_Header     *headers;
    char            *body;
    int             is_complete;

    c_response      *response;
}                   c_request;

#include "../response/response.h"

/* REQUEST.C */
c_request *new_request();
void free_request(c_request *req);
void log_request(c_request *req);

/* BODY.C */
int append_body(c_request *req, char *data);

#endif
