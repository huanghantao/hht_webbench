#ifndef __HHT_LIST_H__
#define __HHT_LIST_H__


#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) hht_list_head_t name = LIST_HEAD_INIT(name)
#define INIT_LIST_HEAD(ptr) do { \
    (ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

typedef struct hht_list_head_s hht_list_head_t;

struct hht_list_head_s {
    hht_list_head_t *next;
    hht_list_head_t *prev;
};

static inline int list_empty(const hht_list_head_t *head)
{
    return head->next == head;
}

#endif /* __HHT_LIST_H__ */