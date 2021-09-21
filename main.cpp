#include <stdio.h>

#include "stack.h"

int main(int argc, char** argv) {

    Stack st = {};
    StackInfo info = {"int", "name", "_file_name_", "_function_", __LINE__};
    stack_ctor(&st, &info);

    push(&st, 12);
    push(&st, 15);
    print_stack(&st);
    dump_stack(&st, "Проверка корректности дампа");

    return 0;
}
