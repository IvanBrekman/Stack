#include <stdio.h>

#include "stack.h"
#include "errorlib.h"

struct Prison {
    char left_executioner[1];
    Stack stack;
    char right_executioner[1];
};

int main(int argc, char** argv) {

    Stack st = {};
    stack_ctor(st);

    printf("Stack size: %zd\n", sizeof(st));

    Prison prison = {{ 0 }, st, { 0 }};

    for (int i = 0; i < (CAP_BORDER + 2) / 2; i++) {
        push(&prison.stack, i + 1);
        if (i == CAP_BORDER / 2) {
            //prison.left_executioner[28] = 14;
        }
    }

    printf("Stack size: %d\n", prison.stack.size);

    printf("left_executioner  address: %p\n"
                  "stack address:             %p\n"
                  "right_executioner address: %p\n"
                  "straight address:          %p\n",
                  &prison.left_executioner[0], &prison.stack, &prison.right_executioner[0], (char*)(&prison.stack));
    printf("%llu\n", Stack_hash_(&prison.stack));
    printf("st.data: %p\n", prison.stack.data);
    prison.left_executioner[24] = 13;
    printf("%llu\n", Stack_hash_(&prison.stack));
    stack_dump(prison.stack, "af");

    int error = 0;
    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        pop(&prison.stack, &error);
    }
    printf("Stack size: %d\n", prison.stack.size);
    printf("!error! %s (code: %d)\n", Stack_error_desc(error), error);
    //print_stack(&prison.stack);

    //printf("%d\n", top(&prison.stack));

    //stack_dump(prison.stack, "Проверка корректности дампа");

    pop(&prison.stack);
    //print_stack(&prison.stack);

    Stack_dtor_(&prison.stack);
    printf("del stack\n");
    //print_stack(&prison.stack);

    return 0;
}
