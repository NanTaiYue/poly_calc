#include "stack.h"

struct list * new_stack() {
	struct list * l = (struct list*)malloc(sizeof(*l));
	if (l == NULL)
		return NULL;
	struct node* one_node = (struct node*)malloc(sizeof(*one_node));
	one_node->next = NULL;
	l->head = one_node;
	l->count = 0;
	return l;
}

void release_stack(struct list *l) {
	struct node *p = l->head->next;
	while (p) {
		struct node *q = p->next;
		free(p);
		p = q;
	}
	free(l->head);
	free(l);
}

int isempty(struct list *l) {
	return l->count > 0 ? 0 : 1;
}

struct node * top(struct list *l) {
	return l->head->next;
}

void push(struct list *l,struct node *p) {
	struct node * first = l->head->next;
	p->next = first;
	l->head->next = p;
	l->count++;
}

struct node * pop(struct list *l) {
	struct node *p = l->head->next;
	l->head->next = p->next;
	l->count--;
	return p;
}