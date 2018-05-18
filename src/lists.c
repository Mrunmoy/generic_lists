/**
 * @file lists.c
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
 *  Function: gl_error_t gl_get_new_node(generic_list_t **ppNode)
 *  Summary : This function allocates and returns a new node on heap
 *  Input	: ppNode - Pointer to node pointer
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
gl_error_t gl_get_new_node(generic_list_t **ppNode)
{
    if (!ppNode)
    {
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
        return List_NullPtrErr;
    }

    if (!*ppNode)
    {
        *ppNode = (generic_list_t *)malloc(sizeof(generic_list_t));
        if (!(*ppNode))
        {
            printf("%s:%d Err: Failed to allocate memory!\r\n", __FUNCTION__, __LINE__);
            return List_MemAllocErr;
        }
        (*ppNode)->pData = NULL;
        (*ppNode)->pNext = NULL;
    }
    else
    {
        printf("%s:%d Err: Pointer is already pointing to some memory!\r\n", __FUNCTION__, __LINE__);
        return List_NotEmptyErr;
    }
    return List_Ok;
}

/*
 *----------------------------------------------------------------------
 *  Function: gl_error_t gl_add_to_front(generic_list_t **ppListHead,
 *            generic_list_t *pNode)
 *  Summary : This function adds a node to the front of list
 *  Input	: ppListHead - Pointer to list head pointer
 *            pNode - Pointer to node to be added
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
gl_error_t gl_add_to_front(generic_list_t **ppListHead, generic_list_t *pNode)
{
    if (!pNode || !ppListHead)
    {
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
        return List_NullPtrErr;
    }

    // if the first node is valid,
    if (*ppListHead)
    {
        // set the new node next to point to head
        pNode->pNext = *ppListHead;
    }
    // point head to the new node
    *ppListHead = pNode;
    return List_Ok;
}

/*
 *----------------------------------------------------------------------
 *  Function: gl_error_t gl_add_to_rear(generic_list_t **ppListHead,
 *            generic_list_t *pNode)
 *  Summary : This function adds a node to the rear of list
 *  Input	: ppListHead - Pointer to list head pointer
 *            pNode - Pointer to node to be added
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
gl_error_t gl_add_to_rear(generic_list_t **ppListHead, generic_list_t *pNode)
{
    if (!pNode || !ppListHead)
    {
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
        return List_NullPtrErr;
    }

    if (!*ppListHead) // if head is empty
    {
        *ppListHead = pNode; // add first node as the head node
    }
    else
    {
        // iterate over list to reach the last node
        generic_list_t *pCurNode = *ppListHead;
        while(pCurNode->pNext)
        {
            pCurNode = pCurNode->pNext; // iterate
        }
        pCurNode->pNext = pNode; // save the new node to the end
        pNode->pNext = NULL; // the end of the node is always NULL
    }
    return List_Ok;
}

/*
 *----------------------------------------------------------------------
 *  Function: gl_error_t gl_remove_from_front(generic_list_t **ppListHead
 *            generic_list_t **pRemovedNode)
 *  Summary : This function removes a node from front of list
 *  Input	: ppListHead - Pointer to list head pointer
 *            pRemovedNode - Pointer to removed node pointer
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
gl_error_t gl_remove_from_front(generic_list_t **ppListHead, generic_list_t **pRemovedNode)
{
    if (!ppListHead || !pRemovedNode)
    {
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
        return List_NullPtrErr;
    }

    if (!*ppListHead)
    {
        printf("%s:%d Err: Empty List Head!\r\n", __FUNCTION__, __LINE__);
        return List_EmptyErr;
    }

    *pRemovedNode = *ppListHead;
    *ppListHead = (*ppListHead)->pNext;

    return List_Ok;
}

/*
 *----------------------------------------------------------------------
 *  Function: gl_error_t gl_remove_from_rear(generic_list_t **ppListHead,
 *            generic_list_t **pRemovedNode)
 *  Summary : This function removes a node from rear of list
 *  Input	: ppListHead - Pointer to list head pointer
 *            pRemovedNode - Pointer to removed node pointer
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
gl_error_t gl_remove_from_rear(generic_list_t **ppListHead, generic_list_t **pRemovedNode)
{
    if (!ppListHead || !pRemovedNode)
    {
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
        return List_NullPtrErr;
    }

    if (!*ppListHead)
    {
        printf("%s:%d Err: Empty List Head!\r\n", __FUNCTION__, __LINE__);
        return List_EmptyErr;
    }

    generic_list_t *pCurNode  = *ppListHead;
    generic_list_t *pPrevNode = *ppListHead;
    while(pCurNode->pNext)
    {
        pPrevNode = pCurNode;
        pCurNode = pCurNode->pNext;
    }

    *pRemovedNode = pCurNode;

    // special case: removing head node
    if (*ppListHead == pCurNode)
    {
        *ppListHead = NULL;
    }
    else
    {
        pPrevNode->pNext = NULL;
    }

    return List_Ok;
}

/*
 *----------------------------------------------------------------------
 *  Function: gl_error_t gl_clear(generic_list_t **ppListHead)
 *  Summary : This function removes and frees all nodes in the list
 *  Input	: ppListHead - Pointer to list head pointer
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
gl_error_t gl_clear(generic_list_t **ppListHead)
{
    if (!ppListHead)
    {
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
        return List_NullPtrErr;
    }

    if (!*ppListHead)
    {
        printf("%s:%d Warn: Empty List Head!\r\n", __FUNCTION__, __LINE__);
        return List_Ok;
    }

    generic_list_t *pCurNode  = *ppListHead;
    while(pCurNode)
    {
        generic_list_t * pNextNode = pCurNode->pNext;
        free(pCurNode);
        pCurNode = pNextNode;
    }

    *ppListHead = NULL;
    return List_Ok;
}

/*
 *----------------------------------------------------------------------
 *  Function: gl_error_t gl_free_node(generic_list_t **ppNode)
 *  Summary : This function frees an allocated node
 *  Input	: ppNode - Pointer to node pointer
 *  Output	: Result of Operation as Enum
 *  Notes	:
 *----------------------------------------------------------------------
 */
gl_error_t gl_free_node(generic_list_t **ppNode)
{
    if (!ppNode)
    {
        printf("%s:%d Err: Null Pointer!\r\n", __FUNCTION__, __LINE__);
        return List_NullPtrErr;
    }

    free(*ppNode);
    *ppNode = NULL;

    return List_Ok;
}
