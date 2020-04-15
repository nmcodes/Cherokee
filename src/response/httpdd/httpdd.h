/*
** httpd.h for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __HTTPDD_H__
#define __HTTPDD_H__

#define HTTPDD_TRUE 1
#define HTTPDD_FALSE 0
#define HTTPDD_END -1

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../request/request.h"
#include "../../config/config.h"
#include "../../utils/file.h"
#include "../content/content.h"

typedef struct                              cherokee_http_decision_diagram {
    int                                     (*test) (c_config *config, c_request *req);
    struct cherokee_http_decision_diagram   *true;
    struct cherokee_http_decision_diagram   *false;
}                                           c_http_decision_diagram;

void resolve_http_decision_diagram(c_config *config, c_request *request);
int is_static_file(c_config *config, c_request *req);
int is_static_location(c_config *config, c_request *req);
int is_static_directory(c_config *config, c_request *req);

int is_get_method(c_config *config, c_request *req);
int is_get_or_head_method(c_config *config, c_request *req);
int is_post_method(c_config *config, c_request *req);
int is_put_method(c_config *config, c_request *req);
int is_delete_method(c_config *config, c_request *req);

int has_method_implemented(c_config *config, c_request *req);

#endif
