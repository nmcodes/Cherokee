/*
** html_static_dir.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "content.h"
#include "../../utils/dir.h"
#include "../../log/log.h"

int html_static_dir(c_config *config, c_request *req) {
    char *dir_name, *html;
    c_dir *dir;
    c_dir_entry *entry;

    if (strlen(req->url) <= 1) {
        dir_name = strdup(config->root_path);
    } else {
        dir_name = malloc(strlen(config->root_path) + strlen(req->url) - 1); // -1 remove starting / from req->url
        strcpy(dir_name, config->root_path);
        strcat(dir_name, req->url + 1); // +1 remove starting / from req->url
    }
    dir = get_dir(dir_name);

    html = malloc(500 * sizeof(char));
    strcpy(html, "<!DOCTYPE html><html><head><title>");
    if (strlen(req->url) > 1) {
        html = realloc(html, strlen(html) + strlen(req->url));
        strcat(html, req->url + 1);
    } else {
        html = realloc(html, strlen(html) + strlen(req->url) + 1);
        strcat(html, req->url);
    }

    html = realloc(html, strlen(html) + 36);
    strcat(html, "</title></head><body><h1>Directory ");
    html = realloc(html, strlen(html) + strlen(req->url) + 1);
    strcat(html, req->url);

    html = realloc(html, strlen(html) + 10);
    strcat(html, "</h1><ul>");

    entry = dir->entries;
    while (entry != NULL) {
        html = realloc(html, strlen(html) + 14);
        strcat(html, "<li><a href='");

        if (strcmp(entry->name, ".") == 0) {
            html = realloc(html, strlen(html) + strlen(req->url) + 1);
            strcat(html, req->url);
        } else if (strcmp(entry->name, "..") == 0) {
            // TODO : FIX
            char *token, *last_token = NULL, *rest = req->url;
            while ((token = strtok_r(rest, "/", &rest))) {
                log_debug("%s", token);
                last_token = token;
            }
            log_debug("rest : %s", rest);
            log_debug("last token : %s", last_token);
        } else {
            html = realloc(html, strlen(html) + strlen(req->url) + strlen(entry->name) + 1);
            strcat(html, req->url);
            strcat(html, entry->name);
        }

        html = realloc(html, strlen(html) + 3);
        strcat(html, "'>");

        html = realloc(html, strlen(html) + strlen(entry->name) + 10);
        strcat(html, entry->name);
        strcat(html, "</a></li>");

        entry = entry->next;
    }
    html = realloc(html, strlen(html) + 20);
    strcat(html, "</ul></body></html>");
    log_debug("HTML : %s", html);

    req->response->status = STATUS_200_OK;
    req->response->body->content = html;
    req->response->body->length = strlen(html);
    req->response->body->is_binary = 0;

    return HTTPDD_END;


    // """

    // {{dirname}}</title>
    //     </head>
    // </html>
    // """
}
