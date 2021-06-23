/* Demo of a list in C */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
     char* string;
     struct node* next;
} Node;


void node_init(Node* n, char* st)
{
  if (n != NULL) {
    n->string = st; 
    n->next = NULL;
  }
}

void free_node_content(Node* n)
{
  if (n != NULL)
    if (n->string != NULL)
      free(n->string);
}


typedef struct {
  Node* head;
  Node* tail;
} list;


void list_init(list* l)
{
  if (l != NULL) {
    l->head = NULL;
    l->tail = NULL;
  }
}

int is_empty(const list* l)
{
  return (l->head == NULL);
}

int list_getlength(const list *l)
{
  Node* n;
  int len = 0;
  for (n = l->head; n != NULL; n = n->next) {
    len++;
  }
  return len;
}

int list_push_front(list** l, const char *st)
{
  Node* n = malloc(sizeof(Node));
  node_init(n, strdup(st));
  if (n != NULL) {
    n->next = (*l)->head;
    (*l)->head = n;
    if ((*l)->tail == NULL) {  //only one element: then head=tail
      (*l)->tail = n;
    }
    return 0;
  }
  return -1; // error
}

int list_push_back(list **l, const char* st)
{

  if (is_empty(*l)) {
    list_push_front(l, st);
  }
  else {
    Node* n = malloc(sizeof(Node));

    if (n != NULL) {
      n->string = strdup(st);
      n->next = NULL;

      (*l)->tail->next = n;

      return 0;
    }
  }
  return -1; // error
}

void list_pop_front(list* l)
{
  if (!is_empty(l)) {
    Node*  n = l->head;
    l->head = l->head->next;
    free_node_content(n);
    free(n);
  }
}

void list_free_content(list* l)
{
  if (l != NULL)
    {
      while (!is_empty(l))
        list_pop_front(l);
    }
}

void list_print(list *l)
{
  Node* n = l->head;
  for (n = l->head; n != NULL; n = n->next) {
    printf("%s, ", n->string);
  }
  printf("\n");
}

int main(int argc, char* argv[])
{

     char s1[] = "Bonjour";
     char s2[] = "Hello";
     char s3[] = "Guten Tag";

     list* mylist = malloc(sizeof(list));
     if (mylist != NULL) {

       list_init(mylist);

       list_push_front(&mylist, s1);
       list_push_front(&mylist, s2);
       list_push_back(&mylist, s3);

       printf("mylist has %d elements: ", list_getlength(mylist));
       list_print(mylist);

       list_pop_front(mylist);
       printf("mylist has %d elements: ", list_getlength(mylist));
       list_print(mylist);

       list_free_content(mylist);
       free(mylist);

       return 0;
     }
     else {
       return 1;
     }
}
