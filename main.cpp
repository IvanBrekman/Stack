#include <cstdio>

#include "stack.h"
#include "tests/test.h"

int main(int argc, char** argv) {
    int exit_code = error_with_second_dtor_call_test();
    printf("exit code: %d", exit_code);

    return 1;
}
