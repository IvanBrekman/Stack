#include <stdio.h>

#include "stack.h"
#include "errorlib.h"

int main(int argc, char** argv) {

    Stack st = {};
    stack_ctor(st);
    int cap = st.capacity;

    for (int i = 0; i < 10 + 4; i++) {
        push(&st, i + 1);
    }
    *((char*)(&st) + 1) = 13;
    print_stack(&st);

    for (int i = 0; i < 10; i++) {
        pop(&st);
    }
    print_stack(&st);

    printf("%d\n", top(&st));

    stack_dump(st, "Проверка корректности дампа");

    pop(&st);
    print_stack(&st);

    Stack_dtor_(&st);
    printf("del stack\n");
    print_stack(&st);

    return 0;
}
