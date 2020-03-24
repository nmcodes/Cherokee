/*
** parser.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

Http_Version parse_version(char *str) {
    char *raw_version;
    char *rest;
    Http_Version v;

    rest = str;

    v.major = 0;
    v.minor = 0;
    raw_version = strtok_r(rest, "HTTP/", &rest);

    v.major = atoi(strtok_r(raw_version, ".", &raw_version));
    v.minor = atoi(strtok_r(raw_version, ".", &raw_version));

    return v;
}

int parse_command(c_request *request, char *raw_cmd) {
    char* token = strtok_r(raw_cmd, " ", &raw_cmd);

    Http_Method method = strToMethod(token);
    if (method == NONE) {
        return -1;
    }
    request->method = method;

    token = strtok_r(NULL, " ", &raw_cmd);
    if (token == NULL) {
        return -1;
    }
    request->url = token;

    token = strtok_r(NULL, " ", &raw_cmd);
    Http_Version version = parse_version(token);
    if (version.major != 1 && version.major != 2) {
        return -1;
    }
    request->version = version;
    request->response->version = version;

    return 0;
}

int parse_header(c_request *req, char *raw_header) {
    Http_Header *parsed_header;
    char        *key;

    parsed_header = malloc(sizeof(Http_Header));
    parsed_header->next = NULL;

    parsed_header->value = trim(strstr(raw_header, ":") + 1);
    key = strtok_r(raw_header, ":", &raw_header);


    for(int i = 0; key[i]; i++){
        key[i] = tolower(key[i]);
    }
    parsed_header->key = key;

    if (parsed_header->key == NULL) {
        printf("Error while parsing %s\n", raw_header);
        return -1;
    }

    add_request_header(req, parsed_header);
    return 0;
}

int parse_headers(c_request *req, char *raw_headers) {
    char *command_line;
    char *raw_header;

    req->headers = NULL;

    command_line = strtok_r(raw_headers, "\n", &raw_headers);
    if (parse_command(req, command_line) < 0) {
        return -1;
    }
    while((raw_header = strtok_r(raw_headers, "\n", &raw_headers))) {
        parse_header(req, raw_header);
    }

    return 0;
}

c_request *parse(char *raw_request) {
    const char *delim = "\r\n\r\n";
    char *raw_headers;
    char *raw_body;
    c_request *req;

    // CREATING THE REQUEST
    req = new_request();
    // SEPARATING HEADERS FROM BODY
    // GET BODY
    raw_body = strstr(raw_request, delim);
    raw_body[0] = '\0';
    raw_body = raw_body + strlen(delim);
    // GET HEADERS
    raw_headers = raw_request;
    // PARSING THEM AND ADD THEM TO THE REQUEST
    if (parse_headers(req, raw_headers) < 0) {
        printf("ERROR: Unable to parse headers\n");
        return NULL;
    }
    // ADDING THE BODY TO THE CONTENT
    if (strlen(raw_body) > 0) {
        append_body(req, raw_body);
    } else {
        req->is_complete = 1;
    }
    // DEBUG
    log_request(req);
    return req;
}
