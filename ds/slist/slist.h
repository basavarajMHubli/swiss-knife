
#ifndef __SLIST_H__
#define __SLIST_H__

#define OFFSET_OF(type, member) (size_t)&(((type *)0)->member)
#define GET_ELEM(node, type, member) \
    (type *)((char *)node - OFFSET_OF(type, member))

#define FOR_EACH_NODE(cur, head) for (cur = head.next; cur; cur = cur->next)

struct s_list {
    struct s_list *next;
};

void list_init(struct s_list *head);
void list_node_init(struct s_list *node);
void list_insert(struct s_list *head, struct s_list *elem_node);
void list_remove(struct s_list *head, struct s_list *elem_node);
void list_deinit(struct s_list *node);

#endif /* __SLIST_H__ */
