/*
** strings.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <ctype.h>

char *trim (char *str) {
    char *ibuf, *obuf;

    if (str) {
        for (ibuf = obuf = str; *ibuf;) {
            while (*ibuf && (isspace (*ibuf)))
                ibuf++;

            if (*ibuf && (obuf != str))
               *(obuf++) = ' ';

            while (*ibuf && (!isspace (*ibuf)))
                *(obuf++) = *(ibuf++);
        }
        *obuf = '\0';
    }
    return (str);
}
