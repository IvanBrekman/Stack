#include <cstdio>

#include "stack.h"
#include "tests/test.h"

int main(int argc, char** argv) {
    int exit_code = normal_work_test();
    printf("exit code: %d", exit_code);

    return 1;
}
