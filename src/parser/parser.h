/*
** parser.h for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __PARSER_H__
#define __PARSER_H__

#include <ctype.h>

#include "../utils/strings.h"
#include "../utils/method.h"
#include "../request/request.h"

c_request *parse(char *data);

#endif
