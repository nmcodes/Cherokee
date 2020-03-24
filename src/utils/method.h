/*
** method.h for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __METHOD_H__
#define __METHOD_H__

#include "../headers/headers.h"

Http_Method strToMethod(char *str);
char *methodToStr(Http_Method m);

#endif
