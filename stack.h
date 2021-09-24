//
// Created by ivanbrekman on 20.09.2021.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#define TYPE "int" //!TODO разбить на 2 define?
typedef int stack_el_t;

#define VALID_PTR(ptr, type) ((ptr) != NULL && (ptr) != (type*)poisons::UNINITIALIZED_PTR && (ptr) != (type*)poisons::FREED_PTR)
#define LOCATION(var) { TYPE, #var, __FILE__, __FUNCTION__, __LINE__ }
#define BOMB 0xDEADA2EA // DEAD AREA

//!TODO Избавиться от инициализации cur_info
#define ASSERT_OK(obj, type, reason) {                    \
    if (type ## _error(obj)) {                            \
        StackInfo cur_info = LOCATION(obj);               \
        type ## _dump_(obj, &cur_info, reason);           \
        assert(0 && "verify failed");                     \
    }                                                     \
} // Нужны ли {}? Потому что тогда при вызове не нужны ;
#define stack_ctor(st) {                                  \
    StackInfo info = LOCATION(st);                        \
    Stack_ctor_(&(st), &info);                            \
}
#define stack_dump(st, reason) {                          \
    StackInfo info = LOCATION(st);                        \
    Stack_dump_(&(st), &info, reason);                    \
}

enum errors {
    NOT_ENOUGH_MEMORY         = -1,

    ST_NULL_PTR               = -3,
    ST_DATA_NULL_PTR          = -4,
    ST_EMPTY                  = -5,
    INCORRECT_ST_SIZE         = -6,
    INCORRECT_ST_CAPACITY     = -7,

    DAMAGED_CANARY            = -8,
    ST_SIZE_EXCEEDED_CAPACITY = -9
};

enum poisons {
    UNINITIALIZED_PTR =  6,
    UNINITIALIZED_INT = -666,

    FREED_ELEMENTS    = -667,
    FREED_PTR         = 12
};

struct Stack {
    const long long  left_canary = BOMB;

    stack_el_t* data = (stack_el_t*)poisons::UNINITIALIZED_PTR;
    int capacity     = poisons::UNINITIALIZED_INT;
    int size         = poisons::UNINITIALIZED_INT;

    struct StackInfo* pr_info = (StackInfo*)poisons::UNINITIALIZED_PTR;

    const long long right_canary = BOMB;
};

struct StackInfo {
    const char* type;
    const char* name;
    const char* file;
    const char* func;
    int line;
};

int  Stack_ctor_(Stack* stack, const StackInfo* info);
void Stack_dtor_(Stack* stack);

int Stack_error(const Stack* stack);

int        push(Stack* stack, stack_el_t value);
int        pop(Stack* stack);
stack_el_t top(const Stack* stack);

int change_capacity(Stack* stack, int new_capacity);

void print_stack(const Stack* stack);
void Stack_dump_(const Stack* stack, const StackInfo* current_info, char reason[]);

#endif //STACK_STACK_H
