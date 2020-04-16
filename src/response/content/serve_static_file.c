/*
** serve_static_file.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "../../log/log.h"
#include "content.h"

int serve_static_file(c_config *config, c_request *req) {
    char *file_path, *extension;
    void *content;

    file_path = get_file_path(config->root_path, req->url);
    extension = get_file_extension(file_path);

    content = read_file(file_path, &req->response->body->length);
    log_debug("SIZEOF CONTENT FROM FILE : %ld", sizeof(content));
    req->response->body->content = content;
    log_debug("CONTENT FROM FILE : %x", req->response->body->content);
    log_debug("BODY CONTENT : %p", req->response->body->content);
    free(file_path);

    add_response_header(req->response, new_content_type_header(extension));
    req->response->body->is_binary = is_binary_content_type(extension);
    add_response_header(req->response, new_content_length_header(req->response->body->length));

    req->response->status = STATUS_200_OK;
    return HTTPDD_END;
}
