/*
** response.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "response.h"
#include "../log/log.h"

c_response *new_response() {
    c_response *response;

    response = malloc(sizeof(c_response));
    response->headers = NULL;
    response->raw = NULL;

    response->body = malloc(sizeof(c_response_body));
    response->body->content = NULL;
    response->body->length = -1;
    response->body->is_binary = -1;

    Http_Status s;
    s.code = 500;
    s.hint = "Internal Server Error";
    response->status = s;

    return response;
}

void free_response(c_response *res) {
    if (res == NULL)
        return;
    if (res->body != NULL) {
        if (res->body->content != NULL)
            free(res->body->content);
        free(res->body);
    }
    if (res->headers != NULL)
        free_headers(res->headers);
    if (res->raw != NULL)
        free(res->raw);
    free(res);
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
    ** 1 = \0
    */
    return 8 + 1 + 3 + 1 + strlen(res->status.hint) + 1 + 1;
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
    return headers_length + 1;
}

int build_command_line(c_response *res, char **raw_command_line) {
    int command_line_length;

    command_line_length = get_command_line_length(res);
    *raw_command_line = malloc(command_line_length);
    memset(*raw_command_line, '\0', command_line_length);
    sprintf(*raw_command_line, "HTTP/%d.%d %d %s\n", res->version.major, res->version.minor, res->status.code, res->status.hint);

    return command_line_length;
}

int build_headers(c_response *res, char **raw_headers){
    Http_Header *h;
    int headers_length;
    int raw_header_length;
    char *raw_header;

    headers_length = get_headers_length(res);
    *raw_headers = malloc(headers_length);
    memset(*raw_headers, '\0', headers_length);

    h = res->headers;
    while (h != NULL) {
        raw_header_length = (int) strlen(h->key) + 2 + (int) strlen(h->value) + 2;
        raw_header = malloc(raw_header_length);
        memset(raw_header, '\0', raw_header_length);
        sprintf(raw_header, "%s: %s\n", h->key, h->value);
        strcat(*raw_headers, raw_header);

        h = h->next;
        free(raw_header);
    }

    return headers_length;
}

int get_response_length(c_response *res, int cmd_line_length, int headers_length) {
    if (res == NULL || res->body == NULL)
        return 0;

    if (res->body->content != NULL) {
        return cmd_line_length + headers_length + 1 + res->body->length;
    }
    return cmd_line_length + headers_length + 1;
}

int add_body_to_response(c_response *res, int cmd_line_length, int headers_length) {
    if (res == NULL || res->body == NULL || res->body->content == NULL || res->raw == NULL) {
        log_debug("NO CONTENT");
        return 0;
    }

    if (res->body->is_binary == CONTENT_TYPE_BINARY) {
        log_debug("BINARY CONTENT");
        memcpy(
            res->raw + cmd_line_length + headers_length + 1,
            res->body->content,
            res->body->length
        );
        return -1;
    } else {
        log_debug("NOT BINARY CONTENT");
        log_debug("res->raw : %s", res->raw);
        log_debug("res->body->content : %s", res->body->content);
        strcat(res->raw, res->body->content);
        log_debug("res->raw : %s", res->raw);
        log_debug("strlen(res->raw) : %d", strlen(res->raw));
        return (int) strlen(res->raw);
    }
}

int build_response(c_response *res) {
    char *raw_command_line;
    char *raw_headers;
    int command_line_length;
    int headers_length;
    int raw_response_length;

    finish_response(res);

    command_line_length = build_command_line(res, &raw_command_line);
    headers_length = build_headers(res, &raw_headers);

    raw_response_length = get_response_length(res, command_line_length, headers_length);
    res->raw = malloc(raw_response_length);
    memset(res->raw, '\0', raw_response_length);

    strcat(res->raw, raw_command_line);
    strcat(res->raw, raw_headers);
    strcat(res->raw, "\n");

    log_debug("ADD BODY TO RESPONSE");
    int l = add_body_to_response(res, command_line_length, headers_length);
    log_debug("L : %d", l);
    // free(raw_command_line);
    // free(raw_headers);

    if (l != -1) {
        return l;
    }
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
      printf("BODY (len=%d): \n%p\n", res->body->length, res->body);
}
