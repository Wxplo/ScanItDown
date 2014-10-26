#include <stdio.h>
#include <assert.h>
#include "list.h"


int main () {

//Création d'une liste 

struct list* n1 = malloc(sizeof(struct list));
n1->value = 1;
n1->next = NULL;

struct list* n2 = malloc(sizeof(struct list));
n2->value = 3;
n2->next = NULL;

struct list* n3 = malloc(sizeof(struct list));
n3->value = 6;
n3->next = NULL;

struct list* n4 = malloc(sizeof(struct list));
n4->value = 5;
n4->next = NULL;

struct list *L = list_empty();
list_push_front(L,n3);
list_push_front(L,n2);
list_push_front(L,n1);
//Test des fonctions 
printf("Longueur de la liste : %zd\n",list_len(L));

printf ("Affichage de la liste : ");
afficherListe(L);

//printf ("list_pop_front : ");
//afficherListe(list_pop_front(L));


}

//Fonction de test afficher une liste 
void afficherListe(struct list *l)
{
	struct list *p=l->next;
	while (p !=NULL)
	{
		printf("%d -> ", p->value);
		p = p->next;
	}
	printf("NULL\n");
}

// Fonctions du TP

struct list* list_empty(void) {

        struct list *sentinel = malloc(sizeof(struct list));
        sentinel->next = NULL;
        return sentinel;
}

size_t list_len(struct list *l)
{
	size_t count=0;
        struct list *p = l->next;
	while (p != NULL)
        {
		count++;
		p = p->next;
         	       
        }

        return count;


}

void list_push_front(struct list *l, struct list *elm) {

	struct list *p;
	p = l->next;
        l->next=elm;
        elm->next=p;


}


struct list* list_find(struct list *l, int value) {

        struct list *p;
        p = l->next;
	while ((p != NULL) && (p->value != value)) 
	{
		p=p->next;
	}
	if (p->value == value)
	{
		return p;
	}
	else
	{
		return NULL;
	}
}

struct list* list_pop_front(struct list *l) {

        l->next->next = NULL;
        return l;

}

/*
 * list_insert(l, elm) inserts elm at the right place into a sorted list
 * (increasing order)
 */
 void list_insert(struct list *l, struct list *elm) {

        struct list *p = l->next;
        struct list *psuiv = l->next->next;
        while ( (psuiv != NULL) && (psuiv->value < elm->value) )
        {
                p = p->next;
                psuiv = psuiv->next;
        }
	elm->next=psuiv;
        p->next = elm;
        
}

void list_sort(struct list *l) {

        struct list *head; 
	struct list *cur;
        head = l->next;
        l->next = NULL;
        cur = head;
	while(head != NULL)
	{	
		head=head->next;
		list_insert (l,(list_pop_front(cur)));
		cur=head;
	}
	
}


/* Iterator */
 
typedef struct list    *iterator;
 
/*
 * list_begin(l) returns an iterator on the head of l
 */
iterator list_begin(struct list *l) {
	iterator = l->suiv;
} 
/*
 * list_is_end(it) true if it is the end of the list
 */
int list_is_end(iterator it){
	return (it->suiv == NULL);
} 
/*
 * list_next(&it) move iterator it to the next position if possible
 */
void list_next(iterator *it){
 	if((*it) != NULL)
	{
		*it = (*it)->suiv;
	}
}
/*
 * list_get(it) returns the current value
 */
int list_get(iterator it){
	return it->value;
}
/*
 * list_insert_at(it, elm) insert elm before the node pointed by it
 */
void list_insert_at(iterator it, struct list *elm){
	elm->next=it;
	
}
/* Iterator */
 
typedef (struct list *l) {
  int    line;
  line = printf("l = [");

  // Iterate using iterators
  for (iterator it = list_begin(l); !list_is_end(it); list_next(&it)) {
    assert(it && it->next);
    if (line > 72) // break long lines
      line = printf("\n     ") - 1;
    line += printf(" %3d;", list_get(it));
  }

  printf("%s]\n", line>72 ? "\n" : " ");


}

