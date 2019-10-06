/**
 * @file demo.c
 * @brief Demo code showing linked list api usage
 * @author Basavaraj M. Hubli
 * @version 1.0
 * @date 2019-10-06
 */

#include <stdio.h>
#include <string.h>
#include "slist.h"

struct employee {
    char name[64];
    int id;
    struct s_node node;
};

int main()
{
    struct s_node list_head;
    struct employee e1, e2;

    // Initialize list head pointer
    list_init(&list_head);

    strcpy(e1.name, "Basavaraj M. H.");
    e1.id = 2558;

    // Initialize node pointer
    strcpy(e2.name, "John Doe");
    e2.id = 4;

    // Insert both nodes into list
    list_insert(&list_head, &e1.node);
    list_insert(&list_head, &e2.node);

    printf("\nInserted node:\n");
    // Iterate over list and print values
    struct s_node *cur = NULL;
    FOR_EACH_NODE(cur, &list_head)
    {
        struct employee *e_ptr = GET_ELEM(cur, struct employee, node);
        printf("Employee name(%s) id(%d)\n", e_ptr->name, e_ptr->id);
    }

    // Delete first node
    list_remove(&list_head, &e1.node);

    printf("\nAfter removing first node:\n");
    // Iterate over list and print values
    cur = NULL;
    FOR_EACH_NODE(cur, &list_head)
    {
        struct employee *e_ptr = GET_ELEM(cur, struct employee, node);
        printf("Employee name(%s) id(%d)\n", e_ptr->name, e_ptr->id);
    }

    // Delete first node
    list_remove(&list_head, &e2.node);

    printf("\nAfter removing last node:\n");
    // Iterate over list and print values
    cur = NULL;
    FOR_EACH_NODE(cur, &list_head)
    {
        struct employee *e_ptr = GET_ELEM(cur, struct employee, node);
        printf("Employee name(%s) id(%d)\n", e_ptr->name, e_ptr->id);
    }
    return 0;
}
