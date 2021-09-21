//
// Created by ivanbrekman on 20.09.2021.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#define STACK_INFO {"int", "name", __FILE__, __FUNCTION__, __LINE__}

typedef int stack_el_t;

enum errors {
    NOT_ENOUGH_MEMORY     = -1,

    ST_NULL_PTR           = -3,
    ST_DATA_NULL_PTR      = -4,
    INCORRECT_ST_SIZE     = -5,
    INCORRECT_ST_CAPACITY = -6
};

enum poisons {
    UNINITIALIZED_PTR =  6,
    UNINITIALIZED_INT = -1,

    FREED_ELEMENTS    = -2,
    FREED_PTR         = 12
};

struct Stack {
    stack_el_t* data = (stack_el_t*)poisons::UNINITIALIZED_PTR;
    int capacity     = poisons::UNINITIALIZED_INT;
    int size         = poisons::UNINITIALIZED_INT;

    struct StackInfo* _info = (StackInfo*)poisons::UNINITIALIZED_PTR;
};

struct StackInfo {
    char type[20];
    char name[20];
    char file[20];
    char func[20];
    int  line;
};

int  stack_ctor(Stack* stack, StackInfo* info);
void stack_dtor(Stack* stack);

int stack_ok(Stack* stack);

int push(Stack* stack, stack_el_t value);
int  pop(Stack* stack);

int change_capacity(Stack* stack, int new_capacity);

void print_stack(Stack* stack);
void  dump_stack(Stack* stack, char reason[]);

#endif //STACK_STACK_H
