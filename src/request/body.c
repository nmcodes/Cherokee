/*
** body.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./request.h"

int append_body(c_request *req, char *data) {
    Http_Header     *content_length_header;
    int             content_length, body_length;
    char            *body;

    if (data != NULL && strlen(data) == 0) {
        return 0;
    }

    content_length_header = find_header(req->headers, "content-length");
    if (content_length_header == NULL) {
        printf("Error while adding body: Unable to find Content-Length header");
        return -1;
    }

    if (req->body == NULL) {
        body_length = 0;
    } else {
        body_length = strlen(req->body);
    }

    content_length = atoi(content_length_header->value);
    if (content_length < (int) (body_length + strlen(data))) {
        printf("Error while adding body : Unable to retrieve content_length");
        return -1;
    }

    body = malloc(body_length + strlen(data) + 1);
    memset(body, '\0', (body_length + strlen(data) + 1));

    memcpy(body, req->body, body_length);
    memcpy(body + body_length, data, strlen(data));
    req->body = body;

    if ((int) strlen(req->body) >= content_length) {
        req->is_complete = 1;
    }
    return 0;
}
