/*
** content_type.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "headers.h"

static volatile Content_Type content_types[] = {
    { "aac", "audio/aac" },
    { "abw", "application/x-abiword" },
    { "arc", "application/octet-stream" },
    { "avi", "video/x-msvideo" },
    { "azw", "application/vnd.amazon.ebook" },
    { "bin", "application/octet-stream" },
    { "bz", "application/x-bzip" },
    { "bz2", "application/x-bzip2" },
    { "csh", "application/x-csh" },
    { "css", "text/css" },
    { "csv", "text/csv" },
    { "doc", "application/msword" },
    { "docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document" },
    { "eot", "application/vnd.ms-fontobject" },
    { "epub", "application/epub+zip" },
    { "gif", "image/gif" },
    { "htm", "text/html" },
    { "html", "text/html" },
    { "ico", "image/x-icon" },
    { "ics", "text/calendar" },
    { "jar", "application/java-archive" },
    { "jpeg", "image/jpeg" },
    { "jpg", "image/jpeg" },
    { "js", "application/javascript" },
    { "json", "application/json" },
    { "mid", "audio/midi" },
    { "midi", "audio/midi" },
    { "mpeg", "video/mpeg" },
    { "mpkg", "application/vnd.apple.installer+xml" },
    { "odp", "application/vnd.oasis.opendocument.presentation" },
    { "ods", "application/vnd.oasis.opendocument.spreadsheet" },
    { "odt", "application/vnd.oasis.opendocument.text" },
    { "oga", "audio/ogg" },
    { "ogv", "video/ogg" },
    { "ogx", "application/ogg" },
    { "otf", "font/otf" },
    { "png", "image/png" },
    { "pdf", "application/pdf" },
    { "ppt", "application/vnd.ms-powerpoint" },
    { "pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation" },
    { "rar", "application/x-rar-compressed" },
    { "rtf", "application/rtf" },
    { "sh", "application/x-sh" },
    { "svg", "image/svg+xml" },
    { "swf", "application/x-shockwave-flash" },
    { "tar", "application/x-tar" },
    { "tif", "image/tiff" },
    { "tiff", "image/tiff" },
    { "ts", "application/typescript" },
    { "ttf", "font/ttf" },
    { "txt", "text/plain" },
    { "vsd", "application/vnd.visio" },
    { "wav", "audio/x-wav" },
    { "weba", "audio/webm" },
    { "webm", "video/webm" },
    { "webp", "image/webp" },
    { "woff", "font/woff" },
    { "woff2", "font/woff2" },
    { "xhtml", "application/xhtml+xml" },
    { "xls", "application/vnd.ms-excel" },
    { "xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet" },
    { "xml", "application/xml" },
    { "xul", "application/vnd.mozilla.xul+xml"},
    { "zip", "application/zip" },
    { "7z", "application/x-7z-compressed" },
    { NULL, NULL},
};

char *get_content_type_value(char *data_type) {
    int i;

    i = 0;
    while (content_types[i].type != NULL) {
        if (strcmp(content_types[i].type, data_type) == 0)
            break;
        i++;
    }
    return content_types[i].value;
}

Http_Header *new_content_type_header(char *data_type) {
    Http_Header *h;


    h = malloc(sizeof(Http_Header));
    h->next = NULL;
    h->key = "Content-Type";
    h->value = get_content_type_value(data_type);
    printf("data type : %s\n", data_type);
    printf("header value : %s\n", h->value);

    return h;
}
