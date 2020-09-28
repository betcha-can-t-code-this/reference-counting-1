#include <stdio.h>
#include "./src/stack.h"

#define UNUSED(x)	((void)(x))

int main(int argc, char **argv)
{
	UNUSED(argc);
	UNUSED(argv);

	if (stack_pool_init() < 0) {
		fprintf(stderr, "Virtual memory exhausted.\n");
		return 1;
	}

	item_t i;

	for (i = 0; i < 10; i++) {
		stack_pool_push(i * 10);
	}

	while (!stack_pool_empty()) {
		printf("%d\n", stack_pool_pop());
	}

	stack_pool_destroy();
	return 0;
}
