#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_stack(struct list *l) {
	printf("栈内数据为: ");
	struct node * p = l->head->next;
	while (p) {
		if (p->type == TYPE_C) {
			printf("%c ", p->d.n);
		} else {
			printf("%d ", p->d.n);
		}
		p = p->next;
	}
	printf("\n");
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("请输入参数，如:9+(3-1)*3+10/2 \n");
		return 0;
	}
	char* src = argv[1];
	printf("表达式为:%s\n", src);

	int count = 1;
	// 1.中缀表达式转后缀表达式
	struct list * ss = new_stack();  // 数字栈
	struct list * op = new_stack();  // 符号栈
	struct list * res = new_stack(); // 后缀表达式结果栈
	while (*src != '\0') {
		// printf("\n第[%d]轮循环\n", count);
		char s = *src;
		struct node *p = (struct node *)malloc(sizeof(*p));
		p->next = NULL;
		if (s >= '0' && s <= '9') {
			int num = 0;
			do {
				num = num * 10 + (s - '0');
				src++;
				s = *src;
			} while(s != '\0' && s >= '0' && s <= '9');
			p->d.n = num;
			p->type = TYPE_N;
			push(ss, p);
		} else {
			p->d.op = s;
			p->type = TYPE_C;
			// printf("当前符号: %c \n", s);
			// 判断当前栈顶的符号的优先级
			struct node * t = top(op);
			if (!t || s == '(') {
				// printf("栈顶为空或者符号为(时，直接进栈\n");
				push(op, p);
			} else if (s == ')') {  // 遇到右括号了
				// 一直弹出到'('
			    struct node *q = pop(op);
			    while (q && q->d.op != '(') {
			    	push(ss, q);
			    	q = pop(op);
			    }
			    free(p);
			    if (q) {
			    	free(q);
			    }
			} else {
				// printf("栈顶符号: %c \n", t->d.op);
				switch(t->d.op) {
				case '-':
				case '+':
				case '(':
				    push(op, p);
				    break;
				case '*':
				case '/':
				    if (s == '-' || s == '+') {
				    	while(!isempty(op)) {
				    		struct node * q = pop(op);
				    		if (q->d.op == '(') {
				    			push(op, q);
				    			break;
				    		}
				    		push(ss, q);
				    	}
				    }
				    push(op, p);
				    break;
				}
			}
			src++;
		}
		// print_stack(ss);
		// print_stack(op);
		count++;
	}
	while (!isempty(op)) {
		struct node *p = pop(op);
		push(ss, p);
	}
	// print_stack(ss);
	while (!isempty(ss)) {
		struct node *p = pop(ss);
		push(res, p);
	}
	print_stack(res);

	while (!isempty(res)) {
		struct node *p = pop(res);
		if (p->type == TYPE_N) {
			push(ss, p);
		} else {
			struct node *b = pop(ss);
			struct node *a = pop(ss);
			int num = 0;
			switch(p->d.op) {
			case '+':
			    num = a->d.n + b->d.n;
			    break;
			case '-':
			    num = a->d.n - b->d.n;
			    break;
			case '*':
			    num = a->d.n * b->d.n;
			    break;
			case '/':
			    num = a->d.n/b->d.n;
			    break;
			}
			a->d.n = num;
			push(ss, a);
			free(b);
			free(p);
		}
	}

	struct node * r = pop(ss);
	printf("最终结果为:%d\n", r->d.n);
	free(r);

	release_stack(op);
	release_stack(ss);
	release_stack(res);
	return 0;
}
