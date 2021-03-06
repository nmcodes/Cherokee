/*
** content.h for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __CONTENT_H__
#define __CONTENT_H__

#include <sys/types.h>
#include <stdio.h>

#include "../../config/config.h"
#include "../../request/request.h"
#include "../../utils/file.h"
#include "../../response/httpdd/httpdd.h"

int serve_static_file(c_config *config, c_request *req);

#endif
