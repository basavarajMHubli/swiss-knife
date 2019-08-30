
#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>
#include <assert.h>

/**
 * @file slist.h
 * @brief This implementation of single linked list is inspired from Openvswitch
 * @author Basavaraj M. H.
 * @version 1.0
 * @date 2019-08-30
 */

#define OFFSET_OF(type, member) (size_t)&(((type *)0)->member)
#define GET_ELEM(node, type, member) \
    (type *)((char *)node - OFFSET_OF(type, member))

#define FOR_EACH_NODE(cur, head) \
    for ((cur) = (head)->next; (cur); (cur) = (cur)->next)

/**
 * @brief Node in single linked list
 */
struct s_node {
    struct s_node *next;
};

void list_init(struct s_node *head);
void list_insert(struct s_node *head, struct s_node *elem_node);
void list_remove(struct s_node *head, struct s_node *elem_node);

/**
 * @brief Initializes head pointer / head node of SLL. Caller must allocate
 *        memory to head pointer
 * @param head Head pointer to be initialised
 */
void
list_init(struct s_node *head)
{
    assert(head && "Head node is NULL");
    head->next = NULL;
    return;
}

/**
 * @brief Inserts elem_node into SLL pointed by head
 *
 * @param head Head pointer of SLL
 * @param elem_node Node to be inserted
 */
void
list_insert(struct s_node *head, struct s_node *elem_node)
{
    struct s_node *cur = head;

    assert(head && "Head node is NULL");

    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = elem_node;
    elem_node->next = NULL;

    return;
}

/**
 * @brief Removes elem_node from SLL
 *
 * @param head Head pointer of SLL
 * @param elem_node Node to be deleted
 */
void
list_remove(struct s_node *head, struct s_node *elem_node)
{
    struct s_node *cur = head;
    struct s_node *prev = NULL;

    assert(head && "Head node is NULL");

    prev = cur;
    while (cur) {
        if (cur == elem_node) {
            prev->next = cur->next;
            break;
        }

        prev = cur;
        cur = cur->next;
    }

    return;
}

#endif /* __SLIST_H__ */
