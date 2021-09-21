//
// Created by ivanbrekman on 20.09.2021.
//

#include <assert.h>
#include <malloc.h>

#include "stack.h"

int stack_ctor(Stack* stack, StackInfo* st_info) {
    assert(stack != NULL);

    stack->size     =  0;
    stack->capacity = 64;
    stack->data     = (stack_el_t *)calloc(stack->capacity, sizeof(stack_el_t));

    stack->_info    = st_info;

    return 0;
}
void stack_dtor(Stack* stack) {
    if (stack_ok(stack) != 0) {
        dump_stack(stack, "stack_ok failed");
        return;
    }

    for (int i = 0; i < stack->size; i++) {
        stack->data[i] = (stack_el_t)poisons::FREED_ELEMENTS;
    }
    free(stack->data);

    stack->data     = (stack_el_t*)poisons::FREED_PTR;
    stack->capacity = poisons::FREED_ELEMENTS;
    stack->size     = poisons::FREED_ELEMENTS;

    free(stack->_info);
    stack->_info = (StackInfo*)poisons::FREED_PTR;
}

int stack_ok(Stack* stack) {
    if (stack == NULL) {
        return errors::ST_NULL_PTR;
    }
    if (stack->data == NULL) {
        return errors::ST_DATA_NULL_PTR;
    }
    if (stack->size < 0) {
        return errors::INCORRECT_ST_SIZE;
    }
    if (stack->capacity < 0) {
        return errors::INCORRECT_ST_CAPACITY;
    }

    return 0;
}

int push(Stack* stack, stack_el_t value) {
    if (stack_ok(stack) != 0) {
        dump_stack(stack, "stack_ok failed in the beginning of push func");
        return -1;
    }

    if (stack->size == stack->capacity) {
        change_capacity(stack, stack->capacity);
    }

    stack->data[stack->size++] = value;

    if (stack_ok(stack) != 0) {
        dump_stack(stack, "stack_ok failed in the end of push func");
        return -1;
    }
    return stack->size;
}
int pop(Stack* stack) {
    if (stack_ok(stack) != 0) {
        dump_stack(stack, "stack_ok failed in the beginning of pop func");
        return -1;
    }

    if (stack->size == 0) {
        return -1;
    }

    stack_el_t del_element = stack->data[stack->size - 1];
    stack->data[--stack->size] = poisons::UNINITIALIZED_INT;

    if (stack->size * 2 <= stack->capacity) {
        change_capacity(stack, stack->capacity / 2);
    }

    if (stack_ok(stack) != 0) {
        dump_stack(stack, "stack_ok failed in the end of pop func");
        return -1;
    }
    return del_element;
}

int change_capacity(Stack* stack, int new_capacity) {
    if (stack_ok(stack) != 0) {
        dump_stack(stack, "stack_ok failed in change_capacity func");
        return -1;
    }

    stack_el_t* stack_data_ptr = (stack_el_t*)realloc(stack->data, new_capacity);
    if (stack_data_ptr == NULL) {
        return errors::NOT_ENOUGH_MEMORY;
    }

    stack->data = stack_data_ptr;
    return new_capacity;
}

void print_stack(Stack* stack) {
    if (stack_ok(stack) != 0) {
        dump_stack(stack, "stack_ok failed in print_stack func");
        return;
    }

    printf("Stack <%s> Size: %d Capacity: %d\n", stack->_info->type, stack->size, stack->capacity);
    for (int i = stack->size - 1; i >= 0; i--) {
        printf("| %2d |\n", stack->data[i]);
    }
    printf(" ++++ \n");
}
void dump_stack(Stack* stack, char reason[]) {
    printf("%s\n", reason);
    if (stack == NULL) {
        printf("Cannot find Stack obj at %p\n", stack);
        return;
    }
    printf("Stack <%s>[%p] (%s) \"%s\" from %s (%d), %s:\n",
           stack->_info->type, stack, stack_ok(stack) == 0 ? "ok" : "FAILED", stack->_info->name, stack->_info->file,
           stack->_info->line, stack->_info->func);

    printf("{\n");
    printf("    Size     = %d\n", stack->size);
    printf("    Capacity = %d\n", stack->capacity);

    printf("    data[%p]\n", stack->data);
    printf("    {\n");
    for (int i = 0; i < stack->capacity; i++) {
        printf("%*s", 8, " ");
        printf("%s", i < stack->size ? "*" : " ");
        printf("[%d] = %d", i, stack->data[i]);
        printf("\n");
    }
    printf("    }\n");

    printf("}\n");
}
