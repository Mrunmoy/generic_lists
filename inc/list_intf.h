#ifndef LISTTEST_LIST_INTF_H
#define LISTTEST_LIST_INTF_H

/**
 * @file list_intf.h
 * @author championsurfer3044 
 * @date 18  May 2018 
 * @brief 
 *
 * Copyright (c) 2018 LIFX
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */


/*
*----------------------------------------------------------------------
*   Include Files
*----------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "lists.h"

/*
*----------------------------------------------------------------------
*   Public Data Types
*----------------------------------------------------------------------
*/

typedef gl_error_t lt_error_code_t;

typedef struct list_type_t
{
    bool                   isInitialized;
    bool                   lock;
    uint16_t               count;
    uint16_t               dataSize;
    struct generic_list_t *pCur;
    struct generic_list_t *pHead;
}list_type_t;

/*
*----------------------------------------------------------------------
*   Public Constants (const)
*----------------------------------------------------------------------
*/


/*
*----------------------------------------------------------------------
*   Public Function Prototypes
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Externs
*----------------------------------------------------------------------
*/
lt_error_code_t lt_initialize(list_type_t *pListContext, uint16_t dataSize);
lt_error_code_t lt_add(list_type_t *pListContext, void *pData);
lt_error_code_t lt_remove(list_type_t *pListContext, void *pData);
lt_error_code_t lt_navigate_next(list_type_t *pListContext);
lt_error_code_t lt_deinit(list_type_t *pListContext);

#endif //LISTTEST_LIST_INTF_H
