/*
** content_type.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "headers.h"

static volatile Content_Type content_types[] = {
    { "aac", "audio/aac", CONTENT_TYPE_BINARY },
    { "abw", "application/x-abiword", CONTENT_TYPE_BINARY },
    { "arc", "application/octet-stream", CONTENT_TYPE_BINARY },
    { "avi", "video/x-msvideo", CONTENT_TYPE_BINARY },
    { "azw", "application/vnd.amazon.ebook", CONTENT_TYPE_BINARY },
    { "bin", "application/octet-stream", CONTENT_TYPE_BINARY },
    { "bz", "application/x-bzip", CONTENT_TYPE_BINARY },
    { "bz2", "application/x-bzip2", CONTENT_TYPE_BINARY },
    { "csh", "application/x-csh", CONTENT_TYPE_BINARY },
    { "css", "text/css", CONTENT_TYPE_NOT_BINARY },
    { "csv", "text/csv", CONTENT_TYPE_NOT_BINARY },
    { "doc", "application/msword", CONTENT_TYPE_BINARY },
    { "docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document", CONTENT_TYPE_BINARY },
    { "eot", "application/vnd.ms-fontobject", CONTENT_TYPE_BINARY },
    { "epub", "application/epub+zip", CONTENT_TYPE_BINARY },
    { "gif", "image/gif", CONTENT_TYPE_BINARY },
    { "htm", "text/html", CONTENT_TYPE_NOT_BINARY },
    { "html", "text/html", CONTENT_TYPE_NOT_BINARY },
    { "ico", "image/x-icon", CONTENT_TYPE_BINARY },
    { "ics", "text/calendar", CONTENT_TYPE_NOT_BINARY },
    { "jar", "application/java-archive", CONTENT_TYPE_BINARY },
    { "jpeg", "image/jpeg", CONTENT_TYPE_BINARY },
    { "jpg", "image/jpeg", CONTENT_TYPE_BINARY },
    { "js", "application/javascript", CONTENT_TYPE_NOT_BINARY},
    { "json", "application/json", CONTENT_TYPE_NOT_BINARY },
    { "mid", "audio/midi", CONTENT_TYPE_BINARY },
    { "midi", "audio/midi", CONTENT_TYPE_BINARY },
    { "mpeg", "video/mpeg", CONTENT_TYPE_BINARY },
    { "mpkg", "application/vnd.apple.installer+xml", CONTENT_TYPE_BINARY },
    { "odp", "application/vnd.oasis.opendocument.presentation", CONTENT_TYPE_BINARY },
    { "ods", "application/vnd.oasis.opendocument.spreadsheet", CONTENT_TYPE_BINARY },
    { "odt", "application/vnd.oasis.opendocument.text", CONTENT_TYPE_BINARY },
    { "oga", "audio/ogg", CONTENT_TYPE_BINARY },
    { "ogv", "video/ogg", CONTENT_TYPE_BINARY },
    { "ogx", "application/ogg", CONTENT_TYPE_BINARY },
    { "otf", "font/otf", CONTENT_TYPE_BINARY },
    { "png", "image/png", CONTENT_TYPE_BINARY },
    { "pdf", "application/pdf", CONTENT_TYPE_BINARY },
    { "ppt", "application/vnd.ms-powerpoint", CONTENT_TYPE_BINARY },
    { "pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation", CONTENT_TYPE_BINARY },
    { "rar", "application/x-rar-compressed", CONTENT_TYPE_BINARY },
    { "rtf", "application/rtf", CONTENT_TYPE_BINARY },
    { "sh", "application/x-sh", CONTENT_TYPE_NOT_BINARY },
    { "svg", "image/svg+xml", CONTENT_TYPE_BINARY },
    { "swf", "application/x-shockwave-flash", CONTENT_TYPE_BINARY },
    { "tar", "application/x-tar", CONTENT_TYPE_BINARY },
    { "tif", "image/tiff", CONTENT_TYPE_BINARY },
    { "tiff", "image/tiff", CONTENT_TYPE_BINARY },
    { "ts", "application/typescript", CONTENT_TYPE_NOT_BINARY },
    { "ttf", "font/ttf", CONTENT_TYPE_BINARY },
    { "txt", "text/plain", CONTENT_TYPE_NOT_BINARY },
    { "vsd", "application/vnd.visio", CONTENT_TYPE_BINARY },
    { "wav", "audio/x-wav", CONTENT_TYPE_BINARY },
    { "weba", "audio/webm", CONTENT_TYPE_BINARY },
    { "webm", "video/webm", CONTENT_TYPE_BINARY },
    { "webp", "image/webp", CONTENT_TYPE_BINARY },
    { "woff", "font/woff", CONTENT_TYPE_BINARY },
    { "woff2", "font/woff2", CONTENT_TYPE_BINARY },
    { "xhtml", "application/xhtml+xml", CONTENT_TYPE_NOT_BINARY },
    { "xls", "application/vnd.ms-excel", CONTENT_TYPE_NOT_BINARY },
    { "xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet", CONTENT_TYPE_BINARY },
    { "xml", "application/xml", CONTENT_TYPE_NOT_BINARY },
    { "xul", "application/vnd.mozilla.xul+xml", CONTENT_TYPE_BINARY},
    { "zip", "application/zip", CONTENT_TYPE_BINARY },
    { "7z", "application/x-7z-compressed", CONTENT_TYPE_BINARY },
    { NULL, NULL, -1 },
};

Content_Type get_content_type(char *data_type) {
    int i;

    i = 0;
    while (content_types[i].type != NULL) {
        if (strcmp(content_types[i].type, data_type) == 0)
            break;
        i++;
    }
    return content_types[i];
}

Http_Header *new_content_type_header(char *data_type) {
    Http_Header *h;


    h = malloc(sizeof(Http_Header));
    h->next = NULL;
    h->key = strdup("Content-Type");
    h->value = get_content_type(data_type).value;

    return h;
}

int is_binary_content_type(char *data_type) {
    return get_content_type(data_type).is_binary;
}
