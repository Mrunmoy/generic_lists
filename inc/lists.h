#ifndef LISTTEST_LISTS_H
#define LISTTEST_LISTS_H

/**
 * @file lists.h
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

/*
*----------------------------------------------------------------------
*   Public Data Types
*----------------------------------------------------------------------
*/
typedef enum gl_error_t
{
    List_UninitErr = 0,
    List_Ok,
    List_MemAllocErr,
    List_NullPtrErr,
    List_NotEmptyErr,
    List_EmptyErr,
    List_FullErr,
    List_EntryNotFoundErr,
    List_MaxErr
}gl_error_t;

typedef struct generic_list_t
{
    void                  *pData;
    struct generic_list_t *pNext;
}generic_list_t;

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

gl_error_t gl_get_new_node(generic_list_t **ppNode);
gl_error_t gl_add_to_front(generic_list_t **ppListHead, generic_list_t *pNode);
gl_error_t gl_add_to_rear(generic_list_t **ppListHead, generic_list_t *pNode);
gl_error_t gl_remove_from_front(generic_list_t **ppListHead, generic_list_t **pRemovedNode);
gl_error_t gl_remove_from_rear(generic_list_t **ppListHead, generic_list_t **pRemovedNode);
gl_error_t gl_clear(generic_list_t **ppListHead);
gl_error_t gl_free_node(generic_list_t **ppNode);


#endif //LISTTEST_LISTS_H
