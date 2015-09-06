#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "slist.h"
#include <set>

using namespace std;

struct element {
   int value;
   struct slist_node next;
};


struct elementList {
   struct slist_head head;
   struct slist_iterator it;
   struct slist_safe_iterator itSafe;
};



void addElementToStack(struct elementList *list, int value)
{
   struct element *e = (struct element *) malloc(sizeof *e);
   SLIST_NODE_INIT(&e->next);
   e->value = value;
   slist_insert_athead(&list->head, &e->next);
}


void addElementToQueue(struct elementList *list, int value)
{
   struct element *e = (struct element *) malloc(sizeof *e);
   SLIST_NODE_INIT(&e->next);
   e->value = value;
   slist_insert_attail(&list->head, &e->next);
}


void removeDuplicates(struct elementList *list)
{
   std::set<int> s;

   slist_safe_iterator_begin(&list->itSafe, &list->head);
   while (!slist_safe_iterator_end(&list->itSafe)) {
      struct element *e;
      e = SLIST_ITER_ENTRY(&list->itSafe, struct element, next);
      std::set<int>::iterator it;
      it = s.find(e->value);
      if (it != s.end()) {
         struct slist_node *n;
         n = slist_safe_iterator_remove(&list->itSafe);
         if (n) {
            free(SLIST_ENTRY(n, struct element, next));
         }
      } else {
         s.insert(e->value);
      }
      slist_safe_iterator_next(&list->itSafe);
   }
}

void display(const char *s, struct elementList *list)
{
   printf("%s\n", s);
   slist_iterator_begin(&list->it, &list->head);
   while (!slist_iterator_end(&list->it)) {
      struct element *e;
      e = SLIST_ITER_ENTRY(&list->it, struct element, next);
      slist_iterator_next(&list->it);
      printf("Value is %d\n", e->value);
   }
   return;
}


int main(int argc, char *argv[])
{
   struct elementList list[2];
   SLIST_HEAD_INIT(&list[0].head);
   SLIST_HEAD_INIT(&list[1].head);

   int i;
   srand(time(NULL));
   for (i = 0; i < 20; i++) {
      addElementToQueue(&list[0], rand() % 20);
   }
   for (i = 0; i < 20; i++) {
      addElementToStack(&list[1], rand() % 20);
   }
   display("Input List", &list[0]);
   display("Input Stack", &list[1]);
   removeDuplicates(&list[0]);
   removeDuplicates(&list[1]);
   display("Modified List", &list[0]);
   display("Modified Stack", &list[1]);
   return 0;
}
