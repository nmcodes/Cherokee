/*
** custom.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "../log/log.h"
#include "../response/response.h"
#include "../utils/strings.h"
#include <Python/Python.h>
#include "custom.h"

void call_python_module(c_response *res, char *folder, char *method) {
    PyObject *pName, *pModule, /**pDict,*/ *pFunc, *pHeaders, *pBody;
    PyObject  *pValue, *pSize;//*pArgs,
    // int i;

    Py_Initialize();
    PySys_SetPath(Py_DecodeLocale(folder, NULL));
    log_debug("Loading file %s/%s.py", folder, method);
    pName = PyUnicode_FromString(method);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule == NULL) {
        PyErr_Print();
        log_error("Failed to load \"%s/%s.py\"", folder, method);
        return ;
    }

    pFunc = PyObject_GetAttrString(pModule, method);
    if (pFunc && PyCallable_Check(pFunc)) {

        pValue = PyObject_CallObject(pFunc, NULL);
        // Py_DECREF(pArgs);
        if (pValue != NULL && PyDict_Check(pValue)) {
            pHeaders = PyDict_GetItemString(pValue, "headers");
            if (PyList_Check(pHeaders)) {
                Py_ssize_t pHeadersSize = PyList_Size(pHeaders);
                pSize = PyLong_FromSsize_t(pHeadersSize);
                long size = PyLong_AsLong(pSize);

                for (long i = 0; i < size; i++) {
                    PyObject *pItem = PyList_GetItem(pHeaders, i);
                    if (pItem) {
                        char *raw_h = strdup(PyUnicode_AsUTF8(pItem));
                        log_debug("h[%d] : %s", i, raw_h);
                        Http_Header *h = malloc(sizeof(Http_Header));
                        h->next = NULL;
                        h->value = trim(strstr(raw_h, ":") + 1);
                        char *key = strtok_r(raw_h, ":", &raw_h);

                        for(int i = 0; key[i]; i++){
                            key[i] = tolower(key[i]);
                        }
                        h->key = key;
                        add_response_header(res, h);
                    }
                }
            }

            pBody = PyDict_GetItemString(pValue, "body");
            res->body->content = strdup(PyUnicode_AsUTF8(pBody));
            res->body->length = (int) strlen(res->body->content);
            res->body->is_binary = 0;
            Py_DECREF(pValue);
        }
        else {
            Py_DECREF(pFunc);
            Py_DECREF(pModule);
            PyErr_Print();
            log_error("Call failed");
            return;
        }
    }
    else {
        if (PyErr_Occurred())
            PyErr_Print();
        log_error("Cannot find function \"%s\"", method);
    }
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);

    Py_Finalize();
    return;
}
