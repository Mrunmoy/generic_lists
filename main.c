#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "list_intf.h"

// custom data structure to be used as node data
typedef struct myds_t
{
    uint8_t field1;
    uint8_t field2;
    uint16_t field3;
    uint32_t field4;
}myds_t;

static myds_t dataHead, data1, data2, data3, data4, data5, data6;


static void create_list(list_type_t *pList)
{
    // clear data
    memset(pList, 0, sizeof(*pList));

    // initialize list
    lt_error_code_t status = lt_initialize(pList, sizeof(myds_t));
    assert(status == List_Ok);
}

static void add_nodes(list_type_t *pList)
{
    // create the list head
    lt_error_code_t status = lt_add(pList, &dataHead);
    assert(status == List_Ok);

    status = lt_add(pList, &data1);
    assert(status == List_Ok);

    status = lt_add(pList, &data2);
    assert(status == List_Ok);

    status = lt_add(pList, &data3);
    assert(status == List_Ok);

    status = lt_add(pList, &data4);
    assert(status == List_Ok);

    status = lt_add(pList, &data5);
    assert(status == List_Ok);

    status = lt_add(pList, &data6);
    assert(status == List_Ok);
}

static void remove_nodes(list_type_t *pList)
{
    // remove node operations
    myds_t ds1, ds2, ds3, ds4, ds5, ds6;
    lt_error_code_t status = lt_remove(pList, &ds1);
    assert(status == List_Ok);

    status = lt_remove(pList, &ds2);
    assert(status == List_Ok);

    status = lt_remove(pList, &ds3);
    assert(status == List_Ok);

    status = lt_remove(pList, &ds4);
    assert(status == List_Ok);

    status = lt_remove(pList, &ds5);
    assert(status == List_Ok);

    status = lt_remove(pList, &ds6);
    assert(status == List_Ok);
}

int main()
{
    list_type_t myList;

    dataHead.field1 = 0;
    data1.field1 = 1;
    data2.field1 = 2;
    data3.field1 = 3;
    data4.field1 = 4;
    data5.field1 = 5;
    data6.field1 = 6;

    create_list(&myList);

    add_nodes(&myList);

    remove_nodes(&myList);

    add_nodes(&myList);

    lt_error_code_t status = List_Ok;

    int i = 0;
    do
    {
        printf("node %d: value %u\n", i++, ((myds_t *)(myList.pCur->pData))->field1 );
        status = lt_navigate_next(&myList);
    } while (List_Ok == status);

    status = lt_deinit(&myList);
    assert(status == List_Ok);

    return 0;
}