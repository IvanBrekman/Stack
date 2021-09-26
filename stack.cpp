//
// Created by ivanbrekman on 20.09.2021.
//

#include <assert.h>
#include <malloc.h>

#include "stack.h"
#include "errorlib.h"

int  Stack_ctor_(Stack* stack, const StackInfo* info, int* error) {
    if (VALIDATE_LEVEL >= 1) {
        assert(VALID_PTR(stack, Stack));
        assert(VALID_PTR(info, StackInfo));
    }
    if (!VALID_PTR(stack, Stack) && VALID_PTR(error, int)) {
        *error = errors::ST_INVALID_PTR;
    }
    if (!VALID_PTR(info, StackInfo) && VALID_PTR(error, int)) {
        *error = errors::ST_INFO_INVALID_PTR;
    }

    stack->size     = 0;
    stack->capacity = CAP_STEP;
    stack->data     = (stack_el_t *)calloc(stack->capacity * sizeof(stack_el_t) + 2 * sizeof(long long), sizeof(char));
    *((long long*)stack->data) = CANARY;
    *((long long*)((char*)stack->data + sizeof(long long) + stack->capacity * sizeof(stack_el_t))) = CANARY;
    stack->data = (stack_el_t*)((char*)stack->data + sizeof(long long));

    stack->pr_info  = (StackInfo*)info;

    if (VALIDATE_LEVEL >= 2) {
        for (int i = 0; i < stack->capacity; i++) {
            stack->data[i] = poisons::UNINITIALIZED_INT;
        }
    }

    if (VALIDATE_LEVEL >= 1) {
        stack_dump(*stack, "check init");
    }

    ASSERT_OK(stack, Stack, "Stack_error failed. Invalid Stack constructor");
    CHECK_SOFT_ERROR(stack, Stack, error);
    return 0;
}
void Stack_dtor_(Stack* stack, int* error) {
    ASSERT_OK(stack, Stack, "Stack_error failed on destructor (maybe repeat dtor call?)");
    CHECK_SOFT_ERROR(stack, Stack, error);

    if (VALIDATE_LEVEL >= 2) {
        for (int i = 0; i < stack->size; i++) {
            stack->data[i] = (stack_el_t)poisons::FREED_ELEMENTS;
        }
    }
    stack->data = (stack_el_t*)((char*)stack->data - sizeof(long long));
    free(stack->data);

    stack->data     = (stack_el_t*)poisons::FREED_PTR;
    stack->capacity = poisons::FREED_ELEMENTS;
    stack->size     = poisons::FREED_ELEMENTS;
}

int   Stack_error(const Stack* stack) {
    if (stack == NULL) {
        return errors::ST_INVALID_PTR;
    }
    if (stack->data == NULL) {
        return errors::ST_DATA_INVALID_PTR;
    }
    if (stack->size < 0) {
        return errors::INCORRECT_ST_SIZE;
    }
    if (stack->capacity < 0) {
        return errors::INCORRECT_ST_CAPACITY;
    }

    long long* l_canary = (long long*)((char*)stack->data - sizeof(long long));
    long long* r_canary = (long long*)((char*)stack->data + stack->capacity * sizeof(stack_el_t));
    if (*l_canary != CANARY || *r_canary != CANARY) {
        return errors::DAMAGED_DATA_CANARY;
    }
    if (stack->left_canary != CANARY || stack->right_canary != CANARY) {
        return errors::DAMAGED_STACK_CANARY;
    }
    if (stack->size > stack->capacity) {
        return errors::ST_SIZE_EXCEEDED_CAPACITY;
    }

    if (VALIDATE_LEVEL >= 2) {
        for (int i = 0; i < stack->size; i++) {
            if (stack->data[i] == poisons::UNINITIALIZED_INT || stack->data[i] == poisons::FREED_ELEMENTS) {
                return errors::BAD_ST_ELEMENT;
            }
        }
    }

    return 0;
}
char* Stack_error_desc(int error_code) {
    switch (error_code) {
        case 0:
            return "No error";
        case errors::NOT_ENOUGH_MEMORY:
            return "Can`t find enough dynamic memory";
        case errors::ST_INVALID_PTR:
            return "Stack has invalid pointer";
        case errors::ST_DATA_INVALID_PTR:
            return "Stack.data has invalid pointer";
        case errors::ST_EMPTY:
            return "Stack is empty";
        case errors::INCORRECT_ST_SIZE:
            return "Stack has incorrect size";
        case errors::INCORRECT_ST_CAPACITY:
            return "Stack has incorrect capacity";
        case errors::ST_SIZE_EXCEEDED_CAPACITY:
            return "Stack size is more then stack capacity";
        case errors::DAMAGED_STACK_CANARY:
            return "Stack damaged. Something messed stack canary";
        case errors::DAMAGED_DATA_CANARY:
            return "Stack damaged. Something messed stack.data canary";
        case errors::BAD_ST_ELEMENT:
            return "Stack element is incorrect";
        default:
            return "Unknown error code";
    }
}

int push(Stack* stack, stack_el_t value, int* error) {
    ASSERT_OK(stack, Stack, "Stack_error failed in the beginning of push func");
    CHECK_SOFT_ERROR(stack, Stack, error);

    if (stack->size == stack->capacity) {
        change_capacity(stack, stack->capacity < CAP_BORDER ? 2 * stack->capacity : stack->capacity + CAP_STEP, error);
    }

    stack->data[stack->size++] = value;

    ASSERT_OK(stack, Stack, "Stack_error failed in the end of push func");
    CHECK_SOFT_ERROR(stack, Stack, error);
    return stack->size;
}
int  pop(Stack* stack, int* error) {
    ASSERT_OK(stack, Stack, "Stack_error failed in the beginning of pop func");
    CHECK_SOFT_ERROR(stack, Stack, error);

    if (stack->size == 0) {
        if (VALIDATE_LEVEL >= 1) {
            StackInfo cur_info = LOCATION(obj);
            Stack_dump_(stack, &cur_info, "Cannot pop from empty stack");
            if (VALIDATE_LEVEL >= 3) {
                Stack_dump_file_(stack, &cur_info, "Cannot pop from empty stack", "log.txt");
            }
            assert(0 && "Cannot pop from empty stack");
        }
        return errors::ST_EMPTY;
    }

    stack_el_t del_element = stack->data[stack->size - 1];
    stack->data[--stack->size] = poisons::FREED_ELEMENTS;

    if (stack->size >= CAP_BORDER && (stack->size + 2 * CAP_STEP) == stack->capacity) {
        change_capacity(stack, stack->capacity - CAP_STEP, error);
    } else if (stack->capacity > CAP_BORDER && stack->size * 2 == CAP_BORDER) {
        change_capacity(stack, stack->capacity - CAP_STEP, error);
    } else if (stack->size >= CAP_STEP && stack->size * 4 == stack->capacity) {
        change_capacity(stack, stack->capacity / 2, error);
    } else if (stack->size == 0) {
        change_capacity(stack, CAP_STEP, error);
    }

    ASSERT_OK(stack, Stack, "Stack_error failed in the end of pop func");
    CHECK_SOFT_ERROR(stack, Stack, error);
    return del_element;
}
stack_el_t top(const Stack* stack, int* error) {
    ASSERT_OK(stack, Stack, "Stack_error failed in top func");
    CHECK_SOFT_ERROR(stack, Stack, error);

    if (stack->size == 0) {
        if (VALIDATE_LEVEL >= 1) {
            StackInfo cur_info = LOCATION(obj);
            Stack_dump_(stack, &cur_info, "Cannot get top element from empty stack");
            if (VALIDATE_LEVEL >= 3) {
                Stack_dump_file_(stack, &cur_info, "Cannot get top element from empty stack", "log.txt");
            }
            assert(0 && "Cannot get top element from empty stack");
        }
        *error = errors::ST_EMPTY;
        return errors::ST_EMPTY;
    }

    return stack->data[stack->size - 1];
}

int change_capacity(Stack* stack, int new_capacity, int* error) {
    ASSERT_OK(stack, Stack, "Stack_error failed in the beginning check_capacity func");
    CHECK_SOFT_ERROR(stack, Stack, error);

    if (VALIDATE_LEVEL >= 1) {
        printf("Capacity:     %d\nSize:         %d\nNew capacity: %d\n\n",
               stack->capacity, stack->size, new_capacity);
    }

    stack->data = (stack_el_t*)((char*)stack->data - sizeof(long long));
    stack_el_t* stack_data_ptr = (stack_el_t*)realloc(stack->data, new_capacity * sizeof(stack_el_t) + 2 * sizeof(long long));
    if (!VALID_PTR(stack_data_ptr, stack_el_t)) {
        *error = errors::NOT_ENOUGH_MEMORY;
        return errors::NOT_ENOUGH_MEMORY;
    }

    *(long long*)((char*)stack_data_ptr + sizeof(long long) + new_capacity * sizeof(stack_el_t)) = CANARY;

    stack->data = (stack_el_t*)((char*)stack_data_ptr + sizeof(long long));
    stack->capacity = new_capacity;

    ASSERT_OK(stack, Stack, "Stack_error failed in the end of change_capacity func")
    CHECK_SOFT_ERROR(stack, Stack, error);
    return new_capacity;
}

void print_stack(const Stack* stack, int* error) {
    ASSERT_OK(stack, Stack, "Stack_error failed in print_stack func");
    CHECK_SOFT_ERROR(stack, Stack, error);

    printf("Stack <%s> Size: %d Capacity: %d\n", stack->pr_info->type, stack->size, stack->capacity);
    for (int i = stack->size - 1; i >= 0; i--) {
        printf("| %2d |\n", stack->data[i]);
    }
    printf(" ++++ \n");
}
void Stack_dump_(const Stack* stack, const StackInfo* current_info, char reason[]) {
    printf((ORANGE "|--------------------             Stack  Dump             --------------------|\n" NATURAL));
    PRINT_DATE(BLUE);
    printf("%s\n", reason);

    int err = Stack_error(stack);
    if (err) printf((RED "%s\n" NATURAL), Stack_error_desc(err));

    if (!VALID_PTR(stack, Stack)) {
        printf((RED "Cannot find Stack obj at %p\n" NATURAL), stack);
        printf((ORANGE "|--------------------COMPILATION DATE %s %s--------------------|\n" NATURAL), __DATE__, __TIME__);
        return;
    }

    printf("Stack <" PURPLE "%s" NATURAL ">[" CYAN "%p" NATURAL "] (%s) " "\"" ORANGE_UNL "%s" NATURAL "\" from %s:%d, " CYAN "%s" NATURAL " function\n",
           current_info->type,
           stack,
           (err) ? (RED "FAILED" NATURAL) : (GREEN "ok" NATURAL),
           current_info->name,
           current_info->file,
           current_info->line,
           current_info->func
           );

    printf("\tStack definition: \"" ORANGE_UNL "%s" NATURAL "\" from %s:%d, " CYAN "%s" NATURAL " function\n",
           stack->pr_info->name, stack->pr_info->file,
           stack->pr_info->line, stack->pr_info->func);

    printf("{\n");

    printf("\tLeft_canary  = %llX (%s)\n",   stack->left_canary,  stack->left_canary  == CANARY ? (GREEN "ok" NATURAL) : (RED "BAD" NATURAL));
    printf("\tRight_canary = %llX (%s)\n\n", stack->right_canary, stack->right_canary == CANARY ? (GREEN "ok" NATURAL) : (RED "BAD" NATURAL));

    if (stack->size > stack->capacity) {
        printf((RED "\tStack size exceeded Stack capacity\n" NATURAL));
    }

    printf("\tSize     = %d", stack->size);
    if      (stack->size == poisons::UNINITIALIZED_INT)     printf((RED " (uninitialized)" NATURAL));
    else if (stack->size == poisons::FREED_ELEMENTS)        printf((RED " (freed)"         NATURAL));
    printf("\n");

    printf("\tCapacity = %d", stack->capacity);
    if      (stack->capacity == poisons::UNINITIALIZED_INT) printf((RED " (uninitialized)" NATURAL));
    else if (stack->capacity == poisons::FREED_ELEMENTS)    printf((RED " (freed)"         NATURAL));
    printf("\n");

    printf("\tdata[" CYAN "%p" NATURAL "]", stack->data);

    if (VALID_PTR(stack->data, stack_el_t)) {
        printf("\n\t{\n");

        long long* l_canary = (long long*)((char*)stack->data - sizeof(long long));
        long long* r_canary = (long long*)((char*)stack->data + stack->capacity * sizeof(stack_el_t));
        printf("\t\t Data left_canary  = %llX (%s)\n",   *l_canary, *l_canary == CANARY ? (GREEN "ok" NATURAL) : (RED "BAD" NATURAL));
        printf("\t\t Data right_canary = %llX (%s)\n\n", *r_canary, *r_canary == CANARY ? (GREEN "ok" NATURAL) : (RED "BAD" NATURAL));

        for (int i = 0; i < stack->capacity; i++) {
            printf("\t\t%s", i < stack->size ? (BLUE "*") : " ");
            printf("[%d]", i);
            if (i < stack->size) printf(NATURAL);
            printf(" = %d", stack->data[i]);
            if     (stack->data[i] == poisons::UNINITIALIZED_INT) printf((RED " (uninitialized)" NATURAL));
            else if(stack->data[i] == poisons::FREED_ELEMENTS)    printf((RED " (freed)"         NATURAL));
            printf("\n");
        }
        printf("    }\n");
    } else {
        printf(" - " RED "No information\n" NATURAL);
    }

    printf("}\n");
    printf(ORANGE "|--------------------COMPILATION DATE %s %s--------------------|" NATURAL "\n", __DATE__, __TIME__);
}
void Stack_dump_file_(const Stack* stack, const StackInfo* current_info, char reason[], const char* log_file) {
    FILE* log = fopen(log_file, "a");

    fprintf(log, "|--------------------             Stack  Dump             --------------------|\n");
    FPRINT_DATE(log);
    fprintf(log, "%s\n", reason);

    int err = Stack_error(stack);
    if (err) fprintf(log, "%s\n", Stack_error_desc(err));

    if (!VALID_PTR(stack, Stack)) {
        fprintf(log, "Cannot find Stack obj at %p\n"
               "|--------------------COMPILATION DATE %s %s--------------------|\n",
               stack, __DATE__, __TIME__);
        return;
    }

    fprintf(log, "Stack <%s>[%p] (%s) \"%s\" from %s:%d, %s function\n"
           "\tStack definition: \"%s\" from %s:%d, %s function\n{\n",
           current_info->type,
           stack,
           (err) ? "FAILED" : "ok",
           current_info->name,
           current_info->file,
           current_info->line,
           current_info->func,

           stack->pr_info->name, stack->pr_info->file,
           stack->pr_info->line, stack->pr_info->func
           );

    fprintf(log, "\tLeft_canary  = %llX (%s)\n",   stack->left_canary,  stack->left_canary  == CANARY ? "ok" : "BAD");
    fprintf(log, "\tRight_canary = %llX (%s)\n\n", stack->right_canary, stack->right_canary == CANARY ? "ok" : "BAD");

    if (stack->size > stack->capacity) {
        fprintf(log, "\tStack size exceeded Stack capacity\n");
    }

    fprintf(log, "\tSize     = %d", stack->size);
    if      (stack->size == poisons::UNINITIALIZED_INT)     fprintf(log, " (uninitialized)");
    else if (stack->size == poisons::FREED_ELEMENTS)        fprintf(log, " (freed)");
    fprintf(log, "\n");

    fprintf(log, "\tCapacity = %d", stack->capacity);
    if      (stack->capacity == poisons::UNINITIALIZED_INT) fprintf(log, " (uninitialized)");
    else if (stack->capacity == poisons::FREED_ELEMENTS)    fprintf(log, " (freed)");
    fprintf(log, "\n");

    fprintf(log, "\tdata[%p]", stack->data);

    if (VALID_PTR(stack->data, stack_el_t)) {
        fprintf(log, "\n\t{\n");

        long long* l_canary = (long long*)((char*)stack->data - sizeof(long long));
        long long* r_canary = (long long*)((char*)stack->data + stack->capacity * sizeof(stack_el_t));
        fprintf(log, "\t\t Data left_canary  = %llX (%s)\n",   *l_canary, *l_canary == CANARY ? "ok" : "BAD");
        fprintf(log, "\t\t Data right_canary = %llX (%s)\n\n", *r_canary, *r_canary == CANARY ? "ok" : "BAD");

        for (int i = 0; i < stack->capacity; i++) {
            fprintf(log, "%*s%s[%d] = %d", 8, " ", i < stack->size ? "*" : " ", i, stack->data[i]);
            if     (stack->data[i] == poisons::UNINITIALIZED_INT) fprintf(log, " (uninitialized)");
            else if(stack->data[i] == poisons::FREED_ELEMENTS)    fprintf(log, " (freed)");
            fprintf(log, "\n");
        }
        fprintf(log, "    }\n");
    } else {
        fprintf(log, " - No information\n");
    }

    fprintf(log, "}\n"
           "|--------------------COMPILATION DATE %s %s--------------------|\n\n",
           __DATE__, __TIME__);

    printf((RED "Dump was written to the file (\"%s\")\n" NATURAL), log_file);
    fclose(log);
}
