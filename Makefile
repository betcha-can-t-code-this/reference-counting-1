CC = gcc
CFLAGS = -O2 -fPIC -Wall -Werror

LIB_OBJS = ./src/stack.o
SHARED_LIB = ./libstack.so

$(SHARED_LIB): $(LIB_OBJS)
	$(CC) -shared -Wl,--export-dynamic $(LIB_OBJS) -o $(SHARED_LIB)

stack_test:
	$(CC) -o stack_test stack_test.c $(shell pwd)/$(SHARED_LIB)

clean:
	rm -f stack_test libstack.so

.PHONY: stack_test clean
