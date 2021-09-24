//
// Created by ivanbrekman on 20.09.2021.
//

//!TODO Доделать канарейки
//!TODO Функция для обработки ошибок (текст ошибки в зависимости от ее кода)
//!TODO Настроить проверки в зависимости от уровня валидации
//!TODO Вывод dump в файл (при необходимом уровне валидации)
//!TODO Изменить обработку для изменения вместимости стека

#include <assert.h>
#include <malloc.h>

#include "stack.h"
#include "errorlib.h"

int Stack_ctor_(Stack* stack, const StackInfo* info) {
    assert(VALID_PTR(stack, Stack));
    assert(VALID_PTR(info, StackInfo));

    stack->size     =  0;
    stack->capacity = 64;
    stack->data     = (stack_el_t *)calloc(stack->capacity, sizeof(stack_el_t));

    stack->pr_info  = (StackInfo*)info;

    ASSERT_OK(stack, Stack, "Stack_error failed. Invalid Stack constructor");
    return 0;
}
void Stack_dtor_(Stack* stack) {
    ASSERT_OK(stack, Stack, "Stack_error failed on destructor (maybe repeat dtor call?)");

    for (int i = 0; i < stack->size; i++) {
        stack->data[i] = (stack_el_t)poisons::FREED_ELEMENTS;
    }
    free(stack->data);

    stack->data     = (stack_el_t*)poisons::FREED_PTR;
    stack->capacity = poisons::FREED_ELEMENTS;
    stack->size     = poisons::FREED_ELEMENTS;

    stack->pr_info  = (StackInfo*)poisons::FREED_PTR;
}

int Stack_error(const Stack* stack) {
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

    if (stack->left_canary != BOMB || stack->right_canary != BOMB) {
        return errors::DAMAGED_CANARY;
    }
    if (stack->size > stack->capacity) {
        return errors::ST_SIZE_EXCEEDED_CAPACITY;
    }

    return 0;
}

int push(Stack* stack, stack_el_t value) {
    ASSERT_OK(stack, Stack, "Stack_error failed in the beginning of push func");

    if (stack->size == stack->capacity) {
        change_capacity(stack, 2 * stack->capacity);
    }

    stack->data[stack->size++] = value;

    ASSERT_OK(stack, Stack, "Stack_error failed in the end of push func");
    return stack->size;
}
int pop(Stack* stack) {
    ASSERT_OK(stack, Stack, "Stack_error failed in the beginning of pop func");

    if (stack->size == 0) {
        return errors::ST_EMPTY;
    }

    stack_el_t del_element = stack->data[stack->size - 1];
    stack->data[--stack->size] = poisons::UNINITIALIZED_INT;

    if (stack->size * 2 <= stack->capacity) {
        change_capacity(stack, stack->capacity / 2);
    }

    ASSERT_OK(stack, Stack, "Stack_error failed in the end of pop func");
    return del_element;
}
stack_el_t top(const Stack* stack) {
    ASSERT_OK(stack, Stack, "Stack_error failed in top func");

    return stack->data[stack->size - 1];
}

int change_capacity(Stack* stack, int new_capacity) {
    ASSERT_OK(stack, Stack, "Stack_error failed in the beginning check_capacity func");

    stack_el_t* stack_data_ptr = (stack_el_t*)realloc(stack->data, new_capacity * sizeof(stack_el_t));
    if (!VALID_PTR(stack_data_ptr, stack_el_t)) {
        return errors::NOT_ENOUGH_MEMORY;
    }

    stack->data = stack_data_ptr;
    stack->capacity = new_capacity;

    ASSERT_OK(stack, Stack, "Stack_error failed in the end of change_capacity func")
    return new_capacity;
}

void print_stack(const Stack* stack) {
    ASSERT_OK(stack, Stack, "Stack_error failed in print_stack func");

    printf("Stack <%s> Size: %d Capacity: %d\n", stack->pr_info->type, stack->size, stack->capacity);
    for (int i = stack->size - 1; i >= 0; i--) {
        printf("| %2d |\n", stack->data[i]);
    }
    printf(" ++++ \n");
}
void Stack_dump_(const Stack* stack, const StackInfo* current_info, char reason[]) {
    printf("%s", colored("|--------------------             Stack  Dump             --------------------|\n", ORANGE));
    printf("%s\n", reason);
    if (Stack_error(stack) == errors::DAMAGED_CANARY) {
        printf("%s\n", colored("Не трожь канарейку!! ТЫ ЗНАЕШЬ СКОЛЬКО ОНА СТОИТ?!!!\nЕще раз увижу - будешь у меня двоичное дерево поиска дебажить с помощью gdb", RED));
    }

    if (stack == NULL) {
        printf("Cannot find Stack obj at %p\n", stack);
        printf("\033[1;33m|--------------------COMPILATION DATE %s %s--------------------|\033[0m\n", __DATE__, __TIME__);
        return;
    }
    printf("Stack <%s>[%p] (%s) \"%s\" from %s:%d, %s function\n",
           colored(current_info->type, PURPLE),
           stack,
           (Stack_error(stack) == 0) ? colored("ok", GREEN) : colored("FAILED", RED),
           current_info->name,
           current_info->file,
           current_info->line,
           current_info->func
           );

    printf("    Stack definition:    ");
    if (VALID_PTR(stack->pr_info, StackInfo)) {
        printf("\"%s\" from %s:%d, %s function\n",
               stack->pr_info->name, stack->pr_info->file,
               stack->pr_info->line, stack->pr_info->func);
    } else {
        printf("%s", colored("No information\n", RED));
    }

    printf("{\n");

    if (stack->size > stack->capacity) {
        printf("    %s", colored("Stack size exceeded Stack capacity\n", RED));
    }

    printf("    Size     = %d", stack->size);
    if      (stack->size == poisons::UNINITIALIZED_INT) printf(" (%s)", colored("uninitialized", RED));
    else if (stack->size == poisons::FREED_ELEMENTS)    printf(" (%s)", colored("freed", RED));
    printf("\n");

    printf("    Capacity = %d", stack->capacity);
    if      (stack->capacity == poisons::UNINITIALIZED_INT) printf(" (%s)", colored("uninitialized", RED));
    else if (stack->capacity == poisons::FREED_ELEMENTS)    printf(" (%s)", colored("freed", RED));
    printf("\n");

    printf("    data[%p]", stack->data);

    if (VALID_PTR(stack->data, stack_el_t)) {
        printf("\n    {\n");
        for (int i = 0; i < stack->capacity; i++) {
            printf("%*s", 8, " ");
            printf("%s", i < stack->size ? "*" : " ");
            printf("[%d] = %d", i, stack->data[i]);
            printf("\n");
        }
        printf("    }\n");
    } else {
        printf(" - %s", colored("No information\n", RED));
    }

    printf("}\n");
    printf("\033[1;33m|--------------------COMPILATION DATE %s %s--------------------|\033[0m\n", __DATE__, __TIME__);
}
