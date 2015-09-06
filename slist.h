#ifndef _SLIST_H
#define _SLIST_H

#include <sys/types.h>
#include <stdint.h>

typedef enum Bool {
   FALSE = 0,
   TRUE = 1,
} Bool;


typedef struct slist_node {
   struct slist_node *next;
} slist_node;


typedef struct slist_head {
   struct slist_node *head;
   struct slist_node *tail;
} slist_head;


typedef struct slist_iterator {
   struct slist_head *head;
   struct slist_node *cursor;
} slist_iterator;


typedef struct slist_safe_iterator {
   struct slist_head *head;
   struct slist_node *cursor, *prevCursor, *nextCursor;
} slist_safe_iterator;


static inline void SLIST_NODE_INIT(slist_node *node)
{
   node->next = NULL;
}

static inline void SLIST_HEAD_INIT(slist_head *head)
{
   head->head = NULL;
   head->tail = NULL;
}


static inline Bool
slist_isempty(slist_head *head)
{
   return head->head == NULL ? TRUE : FALSE;
}


static inline slist_node *
slist_first(slist_head *head)
{
   return head->head;
}


static inline slist_node *
slist_tail(slist_head *head)
{
   return head->tail;
}


static inline slist_node *
slist_next(slist_node *node)
{
   return node->next;
}


static inline void
slist_insert_athead(slist_head *head, slist_node *newNode)
{
   newNode->next = head->head;
   if (head->tail == NULL) {
      head->tail = newNode;
   }
   head->head = newNode;
}


static inline void
slist_insert_attail(slist_head *head, slist_node *newNode)
{
   if (head->tail == NULL) {
      head->head = newNode;
   } else {
      head->tail->next = newNode;
   }
   head->tail = newNode;
   newNode->next = NULL;
}


static inline slist_node *
slist_pop(slist_head *head)
{
   slist_node *first;
   if (head->head == NULL) {
      return NULL;
   }
   first = head->head;
   head->head = first->next;
   if (head->head == NULL) {
      head->tail = NULL;
   }
   first->next = NULL;
   return first;
}


static inline void
slist_insertafter(slist_head *head, slist_node *node, slist_node *newNode)
{
   newNode->next = node->next;
   node->next = newNode;
   if (head->tail == node) {
      head->tail = newNode;
   }
}

static inline void
slist_remove(slist_head *head, slist_node *prevNode, slist_node *node)
{
   if (prevNode) {
      prevNode->next = node->next;
      if (head->tail == node) {
         head->tail = prevNode;
      }
   } else {
      head->head = node->next;
      if (head->tail == node) {
         head->tail = head->head;
      }
   }
}


static inline slist_node *
slist_prev(slist_head *head, slist_node *node)
{
   if (head->head == node) {
      return NULL;
   }
   slist_node *tmp = head->head;
   while (tmp != NULL && tmp->next != node) {
      tmp = tmp->next;
   }
   return tmp;
}


static inline void
slist_removeslow(slist_head *head, slist_node *node)
{
   slist_node *prev = slist_prev(head, node);
   slist_remove(head, prev, node);
}


static inline void
slist_iterator_begin(slist_iterator *iter, slist_head *head)
{
   iter->head = head;
   iter->cursor = slist_first(head);
}


static inline Bool
slist_iterator_end(slist_iterator *iter)
{
   return (iter->cursor == NULL) ? TRUE : FALSE;
}


static inline void
slist_iterator_next(slist_iterator *iter)
{
   iter->cursor = iter->cursor->next;
}


static inline void
slist_safe_iterator_begin(slist_safe_iterator *iter, slist_head *head)
{
   iter->head = head;
   iter->cursor = slist_first(head);
   if (iter->cursor) {
      iter->nextCursor = iter->cursor->next;
   } else {
      iter->nextCursor = NULL;
   }
   iter->prevCursor = NULL;
}


static inline Bool
slist_safe_iterator_end(slist_safe_iterator *iter)
{
   return (iter->cursor == NULL) ? TRUE : FALSE;
}


static inline void
slist_safe_iterator_next(slist_safe_iterator *iter)
{
   iter->prevCursor = iter->cursor;
   iter->cursor = iter->nextCursor;
   if (iter->cursor) {
      iter->nextCursor = iter->cursor->next;
   }
}


static inline slist_node *
slist_safe_iterator_remove(slist_safe_iterator *iter)
{
   slist_node *ptr = iter->cursor;
   if (ptr == NULL) {
      return NULL;
   }
   slist_remove(iter->head, iter->prevCursor, iter->cursor);
   iter->cursor = iter->prevCursor;
   return ptr;
}


#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((uintptr_t) &((TYPE *) 0)->MEMBER)
#endif

#define SLIST_ENTRY(ptr, TYPE, MEMBER) \
   (TYPE *) ((uintptr_t)(ptr) - offsetof(TYPE, MEMBER))

#define SLIST_ITER_ENTRY(iter, TYPE, MEMBER) \
   SLIST_ENTRY((iter)->cursor, TYPE, MEMBER)



#endif
