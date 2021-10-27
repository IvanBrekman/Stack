//
// Created by ivanbrekman on 04.10.2021.
//

#include "../config.h"

#include "../stack.h"

int light_error() {
    // Repeated dtor call!

    Stack st = {};
    stack_ctor(st);

    for (int i = 0; i < 1; i++) {
        push(&st, 1);
    }
    print_stack(&st);

    Stack_dtor_(&st);
    printf("Stack deleted\n");

    // Bad work
    int error = 0;
    printf("\nSecond dtor call\n");
    Stack_dtor_(&st, &error);
    printf("Error code: %d\n", error);
    //

    return 0;
}
int  hard_error() {
    // No check to access stack.info_ values!

    Stack st = {};
    stack_ctor(st);

    for (int i = 0; i < 1; i++) {
        push(&st, 1);
    }
    print_stack(&st);

    // Bad work
    printf("\n");
    printf("stack.info_ address:   %p\n"
           "bad straight address:  %p\n"
           "good straight address: %p\n\n",
           &st.info_, (char*)&st + 48, (char*)&st + 50);
    *((char*)&st + 48) = -13;
    //

    // To check output
    //stack_dump(st, "check");

    int error = 0;
    pop(&st, &error);
    printf("Error code: %d\n", error);

    Stack_dtor_(&st);
    printf("Stack deleted\n");

    return 0;
}
