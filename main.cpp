#include "config.h"

#include <cstdio>

#include "stack.h"
#include "tests/errors_pathogens.h"

int main(int argc, char** argv) {
    int exit_code = hard_error();
    printf("exit code: %d", exit_code);

    return 1;
}
