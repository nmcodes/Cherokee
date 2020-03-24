/*
** main.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __HTTP_H__
#define __HTTP_H__

typedef struct      c_Http_Version {
    int             major;
    int             minor;
}                   Http_Version;

typedef enum {
    GET,
    POST,
    PUT,
    DELETE,
    OPTIONS,
    HEAD,
    NONE
} Http_Method;

#endif
