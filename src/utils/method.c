/*
** method.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <string.h>

#include "./method.h"

Http_Method strToMethod(char *str) {
    if (strcmp(str, "GET") == 0) {
        return GET;
    } else if (strcmp(str, "POST") == 0) {
        return POST;
    } else if (strcmp(str, "PUT") == 0) {
        return PUT;
    } else if (strcmp(str, "DELETE") == 0) {
        return DELETE;
    } else if (strcmp(str, "OPTIONS") == 0) {
        return OPTIONS;
    } else if (strcmp(str, "HEAD") == 0) {
        return HEAD;
    }
    return NONE;
}

char *methodToStr(Http_Method m) {
    if (m == GET)
        return "GET";
    if (m == POST)
        return "POST";
    if (m == PUT)
        return "PUT";
    if (m == DELETE)
        return "DELETE";
    if (m == OPTIONS)
        return "OPTIONS";
    if (m == HEAD)
        return "HEAD";
    return "UNKNOWN";
}
