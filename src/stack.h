#ifndef __STACK_H__
#define __STACK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef int item_t;
typedef size_t refcount_t;

typedef struct stack {
	item_t data;
	struct stack *next;
	struct stack *prev;
} stack_t;

typedef struct stack_pool {
	refcount_t refcount;
	stack_t *head;
	stack_t *current_node;
} stack_pool_t;

int stack_pool_empty(void);
int stack_pool_init(void);
int stack_pool_push(item_t item);
item_t stack_pool_pop(void);
void stack_pool_incref(void);
void stack_pool_decref(void);
void stack_pool_destroy(void);

#ifdef __cplusplus
}
#endif

#endif /* __STACK_H__ */
