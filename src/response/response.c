/*
** response.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "response.h"

c_response *new_response() {
    c_response *response;

    response = malloc(sizeof(c_response));
    response->headers = NULL;
    response->body = NULL;
    response->body_length = -1;
    response->raw = NULL;

    return response;
}

void finish_response(c_response *response) {
    Http_Header *server_header, *date_header;

    server_header = new_server_header();
    date_header = new_date_header();

    add_response_header(response, server_header);
    add_response_header(response, date_header);
}

int get_command_line_length(c_response *res) {
    /*
    ** 8 = HTTP/x.y
    ** 1 = space
    ** 3 = status code
    ** 1 = space
    ** strlen(res->status.hint) : hint length
    ** 1 = \n
    */
    return 8 + 1 + 3 + 1 + strlen(res->status.hint) + 1;
}

int get_headers_length(c_response *res) {
    Http_Header *h;
    int headers_length;

    headers_length = 0;
    h = res->headers;
    while (h != NULL) {
        headers_length += (int) strlen(h->key) + 2 + (int) strlen(h->value) + 1;
        h = h->next;
    }
    return headers_length;
}

int build_response(c_response *res) {
    Http_Header *h;
    char *raw_command_line, *raw_headers, *raw_header, *raw_response;
    int command_line_length, headers_length, raw_header_length, raw_response_length;

    finish_response(res);

    command_line_length = get_command_line_length(res);
    raw_command_line = malloc(command_line_length);
    sprintf(raw_command_line, "HTTP/%d.%d %d %s\n", res->version.major, res->version.minor, res->status.code, res->status.hint);

    headers_length = get_headers_length(res);
    raw_headers = malloc(headers_length);
    memset(raw_headers, '\0', headers_length);

    h = res->headers;
    while (h != NULL) {
        raw_header_length = (int) strlen(h->key) + 2 + (int) strlen(h->value) + 1;
        raw_header = malloc(raw_header_length);
        sprintf(raw_header, "%s: %s\n", h->key, h->value);
        strcat(raw_headers, raw_header);
        h = h->next;
    }

    if (res->body != NULL) {
        raw_response_length = command_line_length + raw_header_length + 1 + res->body_length;
    } else {
        raw_response_length = command_line_length + raw_header_length + 1;
    }
    raw_response = malloc(raw_response_length);
    memset(raw_response, '\0', raw_response_length);

    strcat(raw_response, raw_command_line);
    strcat(raw_response, raw_headers);
    strcat(raw_response, "\n");

    printf("COPYING BODY AT : %d\n", command_line_length + headers_length + 1);
    printf("RAW_RESPONSE AT %d: %c\n", command_line_length + headers_length + 1, raw_response[command_line_length + headers_length + 1]);
    memcpy(raw_response + command_line_length + headers_length + 1, res->body, res->body_length);

    printf("RAW RESPONSE : \n");
    int i =0;
    while (i < raw_response_length) {
        printf("%u ", raw_response[i]);
        i++;
    }
    printf("\n");

    res->raw = raw_response;
    return raw_response_length;
}

void log_response(c_response *res) {
    printf("RESPONSE\n");
    printf("HTTP VERSION : %d.%d\n", res->version.major, res->version.minor);
    printf("status : %d %s\n", res->status.code, res->status.hint);

    Http_Header *header;
    header = res->headers;
    printf("HEADERS : \n");
    while (header->next != NULL) {
        printf("%s=%s\n", header->key, header->value);
        header = header->next;
    }
    printf("%s=%s\n", header->key, header->value);

    if (res->body != NULL)
      printf("BODY (len=%d): \n%p\n", res->body_length, res->body);
}
