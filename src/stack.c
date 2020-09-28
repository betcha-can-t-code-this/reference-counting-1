#include <assert.h>
#include <stdlib.h>
#include "stack.h"

static stack_pool_t pool = {
	.refcount = 0,
	.head = NULL,
	.current_node = NULL
};

int stack_pool_empty(void)
{
	return pool.refcount == 0;
}

int stack_pool_init(void)
{
	pool.head = malloc(sizeof(stack_t));

	if (pool.head == NULL) {
		return -1;
	}

	pool.head->prev = pool.head;
	pool.head->next = NULL;
	pool.current_node = pool.head;

	return 0;
}

int stack_pool_push(item_t item)
{
	stack_pool_incref();

	pool.current_node->data = item;

	return 0;
}

item_t stack_pool_pop(void)
{
	if (stack_pool_empty()) {
		return -1;
	}

	item_t data = pool.current_node->data;

	stack_pool_decref();

	return data;
}

void stack_pool_incref(void)
{
	stack_t *el = malloc(sizeof(stack_t));

	if (el == NULL) {
		return;
	}

	el->prev = pool.current_node;
	el->next = NULL;

	pool.refcount++;
	pool.current_node->next = el;
	pool.current_node = pool.current_node->next;
}

void stack_pool_decref(void)
{
	if (stack_pool_empty()) {
		return;
	}

	stack_t *el = pool.current_node;

	pool.refcount--;
	pool.current_node = pool.current_node->prev;
	pool.current_node->next = NULL;

	free(el);
}

void stack_pool_destroy(void)
{
	assert(stack_pool_empty());
	free(pool.head);

	pool.head = NULL;
	pool.current_node = NULL;
}
