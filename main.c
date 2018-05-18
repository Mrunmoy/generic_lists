#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "lists.h"

// custom data structure to be used as node data
typedef struct myds_t
{
    uint8_t field1;
    uint8_t field2;
    uint16_t field3;
    uint32_t field4;
}myds_t;

int main()
{
    myds_t dataHead, data1, data2, data3, data4, data5, data6;
    generic_list_t *pListHead = NULL;

    // create the list head
    gl_error_t status = gl_get_new_node(&pListHead);
    assert(status == List_Ok);
    pListHead->pData = &dataHead;

    generic_list_t *pNode1 = NULL;
    status = gl_get_new_node(&pNode1);
    assert(status == List_Ok);
    pNode1->pData = &data1;

    generic_list_t *pNode2 = NULL;
    status = gl_get_new_node(&pNode2);
    assert(status == List_Ok);
    pNode2->pData = &data2;

    generic_list_t *pNode3 = NULL;
    status = gl_get_new_node(&pNode3);
    assert(status == List_Ok);
    pNode3->pData = &data3;

    generic_list_t *pNode4 = NULL;
    status = gl_get_new_node(&pNode4);
    assert(status == List_Ok);
    pNode4->pData = &data4;

    generic_list_t *pNode5 = NULL;
    status = gl_get_new_node(&pNode5);
    assert(status == List_Ok);
    pNode5->pData = &data5;

    generic_list_t *pNode6 = NULL;
    status = gl_get_new_node(&pNode6);
    assert(status == List_Ok);
    pNode6->pData = &data6;



    // add node operations
    status = gl_add_to_front(&pListHead, pNode1);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode2);
    assert(status == List_Ok);

    status = gl_add_to_rear(&pListHead, pNode3);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode4);
    assert(status == List_Ok);

    status = gl_add_to_rear(&pListHead, pNode5);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode6);
    assert(status == List_Ok);



    // remove node operations
    generic_list_t *pRN1 = NULL, *pRN2 = NULL, *pRN3 = NULL, *pRN4 = NULL, *pRN5 = NULL, *pRN6 = NULL;
    status = gl_remove_from_front(&pListHead, &pRN1);
    assert(status == List_Ok);

    status = gl_remove_from_front(&pListHead, &pRN2);
    assert(status == List_Ok);

    status = gl_remove_from_front(&pListHead, &pRN3);
    assert(status == List_Ok);

    status = gl_remove_from_front(&pListHead, &pRN4);
    assert(status == List_Ok);

    status = gl_remove_from_front(&pListHead, &pRN5);
    assert(status == List_Ok);

    status = gl_remove_from_front(&pListHead, &pRN6);
    assert(status == List_Ok);

    // free nodes
    status = gl_free_node(&pRN1);
    assert(status == List_Ok);
    status = gl_free_node(&pRN2);
    assert(status == List_Ok);
    status = gl_free_node(&pRN3);
    assert(status == List_Ok);
    status = gl_free_node(&pRN4);
    assert(status == List_Ok);
    status = gl_free_node(&pRN5);
    assert(status == List_Ok);
    status = gl_free_node(&pRN6);
    assert(status == List_Ok);

    // allocate new nodes
    pNode1 = NULL;
    status = gl_get_new_node(&pNode1);
    assert(status == List_Ok);
    pNode1->pData = &data1;

    pNode2 = NULL;
    status = gl_get_new_node(&pNode2);
    assert(status == List_Ok);
    pNode2->pData = &data2;

    pNode3 = NULL;
    status = gl_get_new_node(&pNode3);
    assert(status == List_Ok);
    pNode3->pData = &data3;

    pNode4 = NULL;
    status = gl_get_new_node(&pNode4);
    assert(status == List_Ok);
    pNode4->pData = &data4;

    pNode5 = NULL;
    status = gl_get_new_node(&pNode5);
    assert(status == List_Ok);
    pNode5->pData = &data5;

    pNode6 = NULL;
    status = gl_get_new_node(&pNode6);
    assert(status == List_Ok);
    pNode6->pData = &data6;



    // add node operations
    status = gl_add_to_front(&pListHead, pNode1);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode2);
    assert(status == List_Ok);

    status = gl_add_to_rear(&pListHead, pNode3);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode4);
    assert(status == List_Ok);

    status = gl_add_to_rear(&pListHead, pNode5);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode6);
    assert(status == List_Ok);



    // remove node operations
    status = gl_remove_from_rear(&pListHead, &pRN1);
    assert(status == List_Ok);

    status = gl_remove_from_rear(&pListHead, &pRN2);
    assert(status == List_Ok);

    status = gl_remove_from_rear(&pListHead, &pRN3);
    assert(status == List_Ok);

    status = gl_remove_from_rear(&pListHead, &pRN4);
    assert(status == List_Ok);

    status = gl_remove_from_rear(&pListHead, &pRN5);
    assert(status == List_Ok);

    status = gl_remove_from_rear(&pListHead, &pRN6);
    assert(status == List_Ok);


    // free nodes
    status = gl_free_node(&pRN1);
    assert(status == List_Ok);
    status = gl_free_node(&pRN2);
    assert(status == List_Ok);
    status = gl_free_node(&pRN3);
    assert(status == List_Ok);
    status = gl_free_node(&pRN4);
    assert(status == List_Ok);
    status = gl_free_node(&pRN5);
    assert(status == List_Ok);
    status = gl_free_node(&pRN6);
    assert(status == List_Ok);

    // allocate new nodes
    pNode1 = NULL;
    status = gl_get_new_node(&pNode1);
    assert(status == List_Ok);
    pNode1->pData = &data1;

    pNode2 = NULL;
    status = gl_get_new_node(&pNode2);
    assert(status == List_Ok);
    pNode2->pData = &data2;

    pNode3 = NULL;
    status = gl_get_new_node(&pNode3);
    assert(status == List_Ok);
    pNode3->pData = &data3;

    pNode4 = NULL;
    status = gl_get_new_node(&pNode4);
    assert(status == List_Ok);
    pNode4->pData = &data4;

    pNode5 = NULL;
    status = gl_get_new_node(&pNode5);
    assert(status == List_Ok);
    pNode5->pData = &data5;

    pNode6 = NULL;
    status = gl_get_new_node(&pNode6);
    assert(status == List_Ok);
    pNode6->pData = &data6;


    // add node operations
    status = gl_add_to_front(&pListHead, pNode1);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode2);
    assert(status == List_Ok);

    status = gl_add_to_rear(&pListHead, pNode3);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode4);
    assert(status == List_Ok);

    status = gl_add_to_rear(&pListHead, pNode5);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode6);
    assert(status == List_Ok);



    // remove node operations
    status = gl_remove_from_front(&pListHead, &pRN1);
    assert(status == List_Ok);

    status = gl_remove_from_rear(&pListHead, &pRN2);
    assert(status == List_Ok);

    status = gl_remove_from_front(&pListHead, &pRN3);
    assert(status == List_Ok);

    status = gl_remove_from_rear(&pListHead, &pRN4);
    assert(status == List_Ok);

    status = gl_remove_from_front(&pListHead, &pRN5);
    assert(status == List_Ok);

    status = gl_remove_from_rear(&pListHead, &pRN6);
    assert(status == List_Ok);

    // free nodes
    status = gl_free_node(&pRN1);
    assert(status == List_Ok);
    status = gl_free_node(&pRN2);
    assert(status == List_Ok);
    status = gl_free_node(&pRN3);
    assert(status == List_Ok);
    status = gl_free_node(&pRN4);
    assert(status == List_Ok);
    status = gl_free_node(&pRN5);
    assert(status == List_Ok);
    status = gl_free_node(&pRN6);
    assert(status == List_Ok);

    // allocate new nodes
    pNode1 = NULL;
    status = gl_get_new_node(&pNode1);
    assert(status == List_Ok);
    pNode1->pData = &data1;

    pNode2 = NULL;
    status = gl_get_new_node(&pNode2);
    assert(status == List_Ok);
    pNode2->pData = &data2;

    pNode3 = NULL;
    status = gl_get_new_node(&pNode3);
    assert(status == List_Ok);
    pNode3->pData = &data3;

    pNode4 = NULL;
    status = gl_get_new_node(&pNode4);
    assert(status == List_Ok);
    pNode4->pData = &data4;

    pNode5 = NULL;
    status = gl_get_new_node(&pNode5);
    assert(status == List_Ok);
    pNode5->pData = &data5;

    pNode6 = NULL;
    status = gl_get_new_node(&pNode6);
    assert(status == List_Ok);
    pNode6->pData = &data6;

    // add node operations
    status = gl_add_to_front(&pListHead, pNode1);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode2);
    assert(status == List_Ok);

    status = gl_add_to_rear(&pListHead, pNode3);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode4);
    assert(status == List_Ok);

    status = gl_add_to_rear(&pListHead, pNode5);
    assert(status == List_Ok);

    status = gl_add_to_front(&pListHead, pNode6);
    assert(status == List_Ok);

    // free node operations
    status = gl_clear(&pListHead);
    assert(status == List_Ok);

    return 0;
}