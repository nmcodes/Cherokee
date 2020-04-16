/*
** request.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "request.h"

c_request *new_request() {
    c_request *req;

    req = malloc(sizeof(c_request));
    req->is_complete = 0;
    req->body = NULL;
    req->url = NULL;
    req->response = new_response();

    return req;
}


void free_request(c_request *req) {
    if (req == NULL)
        return;
    if (req->body != NULL)
        free(req->body);
    if (req->headers != NULL) {
        printf("FREEING REQUEST HEADERS");
        free_headers(req->headers);
    }

    //free_response(req->response);
    free(req);
}

void log_request(c_request *req) {
    printf("REQUEST\n");
    printf("METHOD : %d\n", req->method);
    printf("URL : %s\n", req->url);
    printf("HTTP VERSION : %d.%d\n", req->version.major, req->version.minor);

    Http_Header *header;
    header = req->headers;
    printf("HEADERS : \n");
    while (header->next != NULL) {
        printf("%s=%s\n", header->key, header->value);
        header = header->next;
    }
    printf("%s=%s\n", header->key, header->value);

    if (req->body != NULL)
      printf("BODY (len=%ld): \n%s\n", strlen(req->body), req->body);

    printf("REQUEST COMPLETE : %d\n", req->is_complete);
}
