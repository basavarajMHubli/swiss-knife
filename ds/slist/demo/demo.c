
#include <stdio.h>
#include <string.h>
#include "slist.h"

struct employee {
    char name[64];
    int id;
    struct s_list node;
};

int main()
{
    struct s_list list_head;
    struct employee e1, e2;

    // Initialize list head pointer
    list_init(&list_head);

    // Initialize node pointer
    list_node_init(&e1.node);
    strcpy(e1.name, "Basavaraj M. H.");
    e1.id = 3;

    // Initialize node pointer
    list_node_init(&e2.node);
    strcpy(e2.name, "John Doe");
    e2.id = 4;

    // Insert both nodes into list
    list_insert(&list_head, &e1.node);
    list_insert(&list_head, &e2.node);

    // Iterate over list and print values
    struct s_list *cur = NULL;
    FOR_EACH_NODE(cur, list_head)
    {
        struct employee *e_ptr = GET_ELEM(cur, struct employee, node);
        printf("Value: %s id: %d\n", e_ptr->name, e_ptr->id);
    }

    // Delete first node
    list_remove(&list_head, &e1.node);

    // Iterate over list and print values
    cur = NULL;
    FOR_EACH_NODE(cur, list_head)
    {
        struct employee *e_ptr = GET_ELEM(cur, struct employee, node);
        printf("Employee name(%s) id(%d)\n", e_ptr->name, e_ptr->id);
    }
    return 0;
}
