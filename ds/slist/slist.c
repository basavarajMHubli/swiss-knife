
#include <stddef.h>
#include "slist.h"

void
list_init(struct s_list *head)
{
    head->next = NULL;
    return;
}

void
list_node_init(struct s_list *node)
{
    node->next = NULL;
    return;
}

void
list_insert(struct s_list *head, struct s_list *elem_node)
{
    struct s_list *cur = head;

    if (!head) {
        return;
    }

    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = elem_node;
    return;
}

void
list_remove(struct s_list *head, struct s_list *elem_node)
{
    struct s_list *cur = head;
    struct s_list *prev = NULL;

    if (!head) {
        return;
    }

    /* If first node is to be removed */
    if (head == elem_node) {
        head = head->next;
        return;
    }

    prev = cur;
    while (cur) {
        if (elem_node == cur) {
            prev->next = cur->next;
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    return;
}
