#ifndef __HHT_LIST_H__
#define __HHT_LIST_H__


#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) hht_list_head_t name = LIST_HEAD_INIT(name)
#define INIT_LIST_HEAD(ptr) do { \
        (ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)
#define list_entry(ptr, type, member) ({ \
        ((type *)((char *)(ptr) - offsetof(type, member)));})
#define offsetof(type, member) ({ \
    ((size_t)(&((type *)0)->member))})

typedef struct hht_list_head_s hht_list_head_t;

struct hht_list_head_s {
    hht_list_head_t *next;
    hht_list_head_t *prev;
};

static inline int list_empty(const hht_list_head_t *head)
{
    return head->next == head;
}

static inline void list_add(hht_list_head_t *new, hht_list_head_t *prev, hht_list_head_t *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
}

static inline void list_add_head(hht_list_head_t *head, hht_list_head_t *new)
{
    list_add(new, head, head->next);
}

static inline void list_add_tail(hht_list_head_t *head, hht_list_head_t *new)
{
    list_add(new, head->prev, head);
}

#endif /* __HHT_LIST_H__ */