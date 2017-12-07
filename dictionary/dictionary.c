#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

/* *
 * @brief spdIoT_dictionary_element_new
 * */
spdIoTDictionaryElement *spdIoT_dictionary_element_new(void)
{
    spdIoTDictionaryElement *dirElem;

    dirElem = (spdIoTDictionaryElement *) calloc(1, sizeof(spdIoTDictionaryElement));
    if (NULL != dirElem) {
        spdIoT_list_init(&dirElem->list);
        dirElem->key = spdIoT_string_new();
        dirElem->value = spdIoT_string_new();
    }

    return dirElem;
}

/* *
 * @brief spdIoT_dictionary_element_delete
 * */
void spdIoT_dictionary_element_delete(spdIoTDictionaryElement *dirElem)
{
    if (NULL != dirElem) {
        spdIoT_list_del(&dirElem->list);
        if (dirElem->key)
            spdIoT_string_delete(dirElem->key);
        if (dirElem->value)
            spdIoT_string_delete(dirElem->value);

        free(dirElem);
    }
}


/* *
 * @brief spdIoT_dictionary_new
 * */
spdIoTDictionary *spdIoT_dictionary_new(void)
{
    spdIoTDictionary *dictionaryList;

    dictionaryList = (spdIoTDictionary *) calloc(1, sizeof(spdIoTDictionary));
    if (NULL != dictionaryList) {
        spdIoT_list_init(&dictionaryList->list);
        dictionaryList->key = NULL;
        dictionaryList->value = NULL;
    }

    return dictionaryList;
}

/* *
 * @brief spdIoT_dictionary_delete
 * */
void spdIoT_dictionary_delete(spdIoTDictionary *dictionaryList)
{
    spdIoT_dictionary_clear(dictionaryList);
    free(dictionaryList);
}

/* *
 * @brief spdIoT_dictionary_getelement
 * */
spdIoTDictionaryElement *spdIoT_dictionary_getelement(spdIoTDictionary *dir, const char *key)
{
    spdIoTDictionaryElement *dirElem;

    if (NULL == dir || strlen(key) == 0) {
        return NULL;
    }

    spdIoT_list_for_each_entry(dirElem, dir, list) {
        if (strcmp(key, dirElem->key) == 0) {
            return  dirElem;
        }
    }

    return NULL;
}

/* *
 * @brief spdIoT_dictionary_setvalue
 * */
void spdIoT_dictionary_setvalue(spdIoTDictionary *dir, const char *key, const char *value)
{
    spdIoTDictionaryElement *dirElem;

    dirElem = spdIoT_dictionary_getelement(dir, key);
    if (NULL == dirElem) {
        dirElem = spdIoT_dictionary_new();
        spdIoT_dictionary_add(dir, dirElem);
        spdIoT_dictionary_element_setkey(dirElem, key);
    }
    spdIoT_dictionary_element_setvalue(dirElem, value);
}

/* *
 * @brief spdIoT_dictionary_getvalue
 * */
const char *spdIoT_dictionary_getvalue(spdIoTDictionary *dir, const char *key)
{
    spdIoTDictionaryElement *dirElem;

    dirElem = spdIoT_dictionary_getelement(dir, key);
    if (NULL == dirElem) {
        return NULL;
    }

    return spdIoT_dictionary_element_getvalue(dirElem);
}