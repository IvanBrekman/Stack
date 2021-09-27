//
// Created by ivanbrekman on 20.09.2021.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

#define CANARY 0xDEADA2EA // DEAD AREA
#define CAP_STEP    128
#define CAP_BORDER 4096
#define TYPE "int"

#if !defined(VALIDATE_LEVEL)
    #define VALIDATE_LEVEL 2
#endif

#define ASSERT_OK(obj, type, reason) {                               \
    if (VALIDATE_LEVEL >= 1 && type ## _error(obj)) {                \
        StackInfo cur_info = LOCATION(obj);                          \
        type ## _dump_(obj, &cur_info, reason);                      \
        if (VALIDATE_LEVEL >= 3) {                                   \
            type ## _dump_file_(obj, &cur_info, reason, "log.txt");  \
        }                                                            \
        assert(0 && "verify failed");                                \
    }                                                                \
}
#define CHECK_SOFT_ERROR(obj, type, error) {                         \
    if (VALIDATE_LEVEL < 1) {                                        \
        int err = type ## _error(obj);                               \
        if (err && VALID_PTR(error, int)) *(error) = err;            \
    }                                                                \
}
#define stack_ctor(st, size) {                                       \
    StackInfo info = LOCATION(st);                                   \
    Stack_ctor_(&(st), &info, size);                                 \
}
#define stack_dump(st, reason) {                                     \
    StackInfo cur_info = LOCATION(st);                               \
    Stack_dump_(&(st), &cur_info, reason);                           \
}

#include "errorlib.h"

enum errors {
    NOT_ENOUGH_MEMORY         =  -1,

    ST_INVALID_PTR            =  -3,
    ST_DATA_INVALID_PTR       =  -4,
    ST_INFO_INVALID_PTR       =  -5,
    ST_EMPTY                  =  -6,
    INCORRECT_ST_SIZE         =  -7,
    INCORRECT_ST_CAPACITY     =  -8,
    ST_SIZE_EXCEEDED_CAPACITY =  -9,

    DAMAGED_STACK_CANARY      = -10,
    DAMAGED_DATA_CANARY       = -11,
    BAD_ST_ELEMENT            = -12
};

struct Stack {
    const long long left_canary = CANARY;

    void* data   = (void*)poisons::UNINITIALIZED_PTR;
    int el_size  = poisons::UNINITIALIZED_ELEMENT;
    int capacity = poisons::UNINITIALIZED_ELEMENT;
    int size     = poisons::UNINITIALIZED_ELEMENT;

    const struct StackInfo* pr_info = (StackInfo*)poisons::UNINITIALIZED_PTR;

    const long long right_canary = CANARY;
};

struct StackInfo {
    const char* type;
    const char* name;
    const char* file;
    const char* func;
    int line;
};

int  Stack_ctor_(Stack* stack, const StackInfo* info, int el_size, int* error=NULL);
void Stack_dtor_(Stack* stack, int* error=NULL);

int   Stack_error(const Stack* stack);
char* Stack_error_desc(int error_code);

int  push(Stack* stack, void* value, int* error=NULL);
void* pop(Stack* stack, int* error=NULL);
void* top(const Stack* stack, int* error=NULL);

int change_capacity(Stack* stack, int new_capacity, int* error=NULL);

void print_stack     (const Stack* stack, int* error=NULL);
void Stack_dump_     (const Stack* stack, const StackInfo* current_info, char reason[]);
void Stack_dump_file_(const Stack* stack, const StackInfo* current_info, char reason[], const char* log_file);

#endif //STACK_STACK_H
