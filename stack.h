#ifndef STACK_H
#define STACK_H
// 链栈的实现
// 欲实现链栈，需先实现链表
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define TYPE_C 0
#define TYPE_N 1

struct node {
	union {
		char op;
		int n;
	} d;
	int type;
	struct node * next;
};

struct list {
	struct node * head;
	int count;
};


int isempty(struct list *l);
struct list * new_stack();
void release_stack(struct list *l);
void push(struct list *l, struct node *p);
struct node * pop(struct list *l);
struct node * top(struct list *l);

#endif