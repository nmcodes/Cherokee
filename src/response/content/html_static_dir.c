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

    html = malloc(600 * sizeof(char));
    strcpy(html, "<!DOCTYPE html><html><head><title>");
    log_debug("HTML : %s", html);
    if (strlen(req->url) > 1) {
        html = realloc(html, strlen(html) + strlen(req->url));
        strcat(html, req->url + 1);
        log_debug("HTML : %s", html);
    } else {
        html = realloc(html, strlen(html) + strlen(req->url) + 1);
        strcat(html, req->url);
        log_debug("HTML : %s", html);
    }
    html = realloc(html, strlen(html) + 36);
    strcat(html, "</title></head><body><h1>Directory ");
    log_debug("HTML : %s", html);
    html = realloc(html, strlen(html) + strlen(req->url) + 1);
    strcat(html, req->url);
    log_debug("HTML : %s", html);

    html = realloc(html, strlen(html) + 10);
    strcat(html, "</h1><ul>");
    log_debug("HTML : %s", html);

    entry = dir->entries;
    while (entry != NULL) {
        html = realloc(html, strlen(html) + 14);
        strcat(html, "<li><a href='");

        if (strcmp(entry->name, ".") == 0) {
            log_debug("HTML : %s", html);
            html = realloc(html, strlen(html) + strlen(req->url) + 1);
            strcat(html, req->url);
            log_debug("HTML : %s", html);
        } else if (strcmp(entry->name, "..") == 0) {
            // TODO : FIX
            char *current_dir = strdup(req->url);
            if (current_dir[strlen(current_dir)-1] == '/') {
                current_dir[strlen(current_dir)-1] = 0;
            }
            char *lastSlash = strrchr(current_dir, '/');
            if (lastSlash == NULL) {
                current_dir = strdup(req->url);
            } else if (*lastSlash != 0) {
                *(lastSlash +1) = 0;
            }
            html = realloc(html, strlen(html) + strlen(current_dir) + 1);
            strcat(html, strdup(current_dir));
            log_debug("HTML : %s", html);
        } else {
            html = realloc(html, strlen(html) + strlen(req->url) + 2 + strlen(entry->name) + 2);
            strcat(html, req->url);
            log_debug("HTML : %s", html);
            if (req->url[strlen(req->url) -1] != '/') {
                strcat(html, "/");
                log_debug("HTML : %s", html);
            }
            strcat(html, entry->name);
            log_debug("HTML : %s", html);
        }

        html = realloc(html, strlen(html) + 3);
        strcat(html, "'>");
        log_debug("HTML : %s", html);

        html = realloc(html, strlen(html) + strlen(entry->name) + 11);
        strcat(html, entry->name);
        strcat(html, "</a></li>");
        log_debug("HTML : %s", html);

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
