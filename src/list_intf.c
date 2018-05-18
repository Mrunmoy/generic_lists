/**
 * @file list_intf.c
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
#include <assert.h>
#include "list_intf.h"


/*
*----------------------------------------------------------------------
*   Private Defines
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Macros
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Data Types
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Public Variables
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Variables (static)
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Public Constants (const)
*----------------------------------------------------------------------
*/


/*
*----------------------------------------------------------------------
*   Private Constants (static)
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Function Prototypes (static)
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Externs
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Functions Definitions
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Exported Functions Definitions
*----------------------------------------------------------------------
*/
/*
 *----------------------------------------------------------------------
 *  Function: gl_error_t lt_initialize(list_type_t *pListContext)
 *  Summary : This function initializes a list context for list operation
 *  Input	: pListContext - Pointer to List Context
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
lt_error_code_t lt_initialize(list_type_t *pListContext, uint16_t dataSize)
{
    if (!pListContext)
    {
#ifdef DEBUG_LIST_DRIVER
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
#endif
        return List_NullPtrErr;
    }

    pListContext->count         = 0;
    pListContext->lock          = false;
    pListContext->dataSize      = dataSize;
    pListContext->pCur          = NULL;
    pListContext->pHead         = NULL;
    pListContext->isInitialized = true;

    return List_Ok;
}

/*
 *----------------------------------------------------------------------
 *  Function: lt_error_code_t lt_add(list_type_t *pListContext, void *pData)
 *  Summary : This function adds new data node to the list
 *  Input	: pListContext - Pointer to List Context
 *            pData - pointer to data for the node to be added
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
lt_error_code_t lt_add(list_type_t *pListContext, void *pData)
{
    if (!pListContext || !pData)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
#endif
        return List_NullPtrErr;
    }

    if (!pListContext->isInitialized)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: List initialized!\r\n", __FUNCTION__, __LINE__);
#endif
        return List_UninitErr;
    }

    if (pListContext->lock)
    {
        return List_BusyErr;
    }

    // lock list for operation
    pListContext->lock = true;

    generic_list_t *pNode = NULL;
    lt_error_code_t status = gl_get_new_node(&pNode);
    if ((List_Ok != status) ||!pNode)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: Failed to allocate memory!\r\n", __FUNCTION__, __LINE__);
#endif
        pListContext->lock = false;
        return status;
    }

    pNode->pData = malloc(pListContext->dataSize);
    if (!pNode->pData)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: Failed to allocate memory!\r\n", __FUNCTION__, __LINE__);
#endif
        pListContext->lock = false;
        return List_MemAllocErr;
    }
    // copy data into pData
    memcpy(pNode->pData, pData, pListContext->dataSize);


    // set current to start of head was null
    if (!pListContext->pHead)
    {
        pListContext->pCur = pNode;
    }

    // add to rear
    status = gl_add_to_rear(&pListContext->pHead, pNode);
    if (List_Ok != status)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: Failed to add new node!\r\n", __FUNCTION__, __LINE__);
#endif
        pListContext->lock = false;
        return status;
    }

    // keep track of number of nodes
    pListContext->count++;

    // unlock list
    pListContext->lock = false;

    return List_Ok;
}

/*
 *----------------------------------------------------------------------
 *  Function: lt_error_code_t lt_remove(list_type_t *pListContext, void *pData)
 *  Summary : This function removes a data node from the list
 *  Input	: pListContext - Pointer to List Context
 *            ppData - pointer to container to store removed data
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
lt_error_code_t lt_remove(list_type_t *pListContext, void *pData)
{
    if (!pListContext || !pData)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
#endif
        return List_NullPtrErr;
    }

    if (!pListContext->isInitialized)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: List initialized!\r\n", __FUNCTION__, __LINE__);
#endif
        return List_UninitErr;
    }

    if (pListContext->lock)
    {
        return List_BusyErr;
    }

    // lock list for operation
    pListContext->lock = true;

    generic_list_t *pNode = NULL;
    lt_error_code_t status = gl_remove_from_rear(&pListContext->pHead, &pNode);
    if ((List_Ok != status) ||!pNode)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: No node removed!\r\n", __FUNCTION__, __LINE__);
#endif
        pListContext->lock = false;
        return status;
    }

    // copy data into pData
    memcpy(pData, pNode->pData, pListContext->dataSize);

    // keep track of number of nodes
    pListContext->count--;

    // add to rear
    status = gl_free_node(&pNode);
    if (List_Ok != status)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: Failed to free node!\r\n", __FUNCTION__, __LINE__);
#endif
        pListContext->lock = false;
        return status;
    }

    // unlock list
    pListContext->lock = false;

    return List_Ok;
}


/*
 *----------------------------------------------------------------------
 *  Function: lt_error_code_t lt_navigate_next(list_type_t *pListContext)
 *  Summary : This function navigates to next valid node in the list
 *  Input	: pListContext - Pointer to List Context
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
lt_error_code_t lt_navigate_next(list_type_t *pListContext)
{
    if (!pListContext)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
#endif
        return List_NullPtrErr;
    }

    if (!pListContext->isInitialized)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: List initialized!\r\n", __FUNCTION__, __LINE__);
#endif
        return List_UninitErr;
    }

    if (pListContext->lock)
    {
        return List_BusyErr;
    }

    // lock list
    pListContext->lock = true;

    // go to next only if the last one is not null
    if (pListContext->pCur)
    {
        pListContext->pCur = pListContext->pCur->pNext;

        if (!pListContext->pCur)
        {
            pListContext->pCur = pListContext->pHead;
            pListContext->lock = false;
            return List_EndErr;
        }
    }

    // unlock list
    pListContext->lock = false;

    return List_Ok;
}


/*
 *----------------------------------------------------------------------
 *  Function: lt_error_code_t lt_deinit(list_type_t *pListContext)
 *  Summary : This function deinitializes list
 *  Input	: pListContext - Pointer to List Context
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
lt_error_code_t lt_deinit(list_type_t *pListContext)
{
    if (!pListContext)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
#endif
        return List_NullPtrErr;
    }

    if (!pListContext->isInitialized)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: List initialized!\r\n", __FUNCTION__, __LINE__);
#endif
        return List_UninitErr;
    }

    if (pListContext->lock)
    {
        return List_BusyErr;
    }

    // lock list for operation
    pListContext->lock = true;

    lt_error_code_t status = gl_clear(&pListContext->pHead);
    if (List_Ok != status)
    {
#ifdef DEBUG_LIST_INTF
        printf("%s:%d Err: Failed to clear list!\r\n", __FUNCTION__, __LINE__);
#endif
        pListContext->lock = false;
        return status;
    }

    // clear
    pListContext->count = 0;
    pListContext->pCur = NULL;
    pListContext->pHead = NULL;
    pListContext->dataSize = 0;
    pListContext->isInitialized = false;

    // unlock
    pListContext->lock = false;

    return List_Ok;
}
