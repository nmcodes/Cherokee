/*
** httpdd.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "httpdd.h"

c_http_decision_diagram d_serve_static_file = { serve_static_file, NULL, NULL };
c_http_decision_diagram d_not_found = { not_found, NULL, NULL };
c_http_decision_diagram d_static_file_is_get = { is_get_method, &d_serve_static_file, NULL };
c_http_decision_diagram d_static_file = { is_static_file, &d_static_file_is_get, &d_not_found };

c_http_decision_diagram d_static_dir = { is_static_directory, NULL, &d_static_file };

c_http_decision_diagram d_custom_location = { serve_custom_location, NULL, NULL };
c_http_decision_diagram d_method_implemented = { has_method_implemented, &d_custom_location, NULL };

c_http_decision_diagram d_static_location = { is_static_location, &d_static_dir, &d_method_implemented };
c_http_decision_diagram *diagram = &d_static_location;


void resolve_http_decision_diagram(
    c_config *config,
    c_request *request
) {
    c_http_decision_diagram    *current_diagram;
    int                        test_result;

    current_diagram = diagram;

    while (current_diagram != NULL && current_diagram->test != NULL) {
        if ((test_result = current_diagram->test(config, request)) == HTTPDD_TRUE)
            current_diagram = current_diagram->true;
        else if (test_result == HTTPDD_FALSE)
            current_diagram = current_diagram->false;
        else if (test_result == HTTPDD_END)
            break;
    }

}
