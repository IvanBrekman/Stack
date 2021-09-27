#include <stdio.h>

#define VALIDATE_LEVEL 0

#include "stack.h"
#include "errorlib.h"

struct Prison {
    int left_executioner[1];
    Stack stack;
    int right_executioner[1];
};

int main(int argc, char** argv) {
    Stack st = {};
    stack_ctor(st, sizeof(char));

    Prison prison = {{ 0 }, st, { 0 }};

    for (int i = 0; i < (CAP_BORDER + 6 * CAP_STEP) / 2; i++) {
        char number = 'a' + i % 27;
        push(&prison.stack, &number);
        //if (i == CAP_BORDER / 2) *((char*)prison.stack.data - 8) = 127;
    }

    printf("Stack size: %d\n", prison.stack.size);

//    printf("left_executioner  address: %p\n"
//                  "stack address:             %p\n"
//                  "right_executioner address: %p\n"
//                  "straight address:          %p\n",
//                  prison.left_executioner, &prison.stack.size, prison.right_executioner, (char*)(&prison.stack));
    //*(prison.stack.data + -1) = 13;
    //stack_dump(prison.stack, "af");

    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        pop(&prison.stack);
    }
    printf("Stack size: %d\n", prison.stack.size);
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
