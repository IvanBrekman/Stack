//
// Created by ivanbrekman on 04.10.2021.
//

#include "../config.h"

#include "../stack.h"
#include "test.h"

#define DEFINE_STACK                    \
    Stack st = {};                      \
    stack_ctor(st);                     \
                                        \
    Prison prison = {{ 0 }, st, { 0 }}

#define TYPICAL_ENDING                  \
    Stack_dtor_(&prison.stack);         \
    printf("Stack deleted\n");          \
                                        \
    printf(RED "|--------------------     End of test     --------------------|\n" NATURAL)

//! Function testing Stack. Trying to push and then pop elements with extracting top element
//! \param stack pointer to Stack
//! \return      0 if all is good
int is_stack_broken_test(Stack* stack) {
    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        push(stack, i + 1);
    }

    int error = 0;
    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        stack_el_t top_el = top(stack, &error);
        stack_el_t del_el = pop(stack, &error);

        if (top_el != del_el) {
            printf("Top stack element(%d) dont equal with deleted stack element(%d)",
                   top_el, del_el);
            return -1;
        }
    }

    if (error != 0) return error;

    return 0;
}

int normal_work_test() {
    printf(RED "|-------------------     Start of test     -------------------|\n" NATURAL);
    printf(GREEN "This is normal test\n"
                 "Program should end with exit code 0\n\n"
           NATURAL);

    DEFINE_STACK;

    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        push(&prison.stack, i + 1);
    }

    int error = 0;
    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        pop(&prison.stack, &error);
    }

    // Expected output - !Attention! No error (code: 0)
    printf("!Attention! %s (code: %d)\n", Stack_error_desc(error), error);

    TYPICAL_ENDING;

    return 0;
}
int error_with_second_dtor_call_test() {
    printf(RED "|-------------------     Start of test     -------------------|\n" NATURAL);
    printf(GREEN "This is test, where someone called stack dtor again\n"
                 "If VALIDATE_LEVEL == NO_VALIDATE:   program should end with exit code   0 and variable error = -4\n"
                 "If VALIDATE_LEVEL >= WEAK_VALIDATE: program should fall with SIGABRT      and variable error = -4\n"
                 "                                    Also should be:\n"
                 "                                      1. init dump\n"
                 "                                      2. info about changing capacity\n"
                 "                                      3. dump with error (Stack_error failed on destructor (maybe repeat dtor call?))\n"
                 "Program can exit with exit code 0 or fall with SIGABRT\n\n"
           NATURAL);

    DEFINE_STACK;

    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        push(&prison.stack, i + 1);
    }

    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        pop(&prison.stack);
    }

    Stack_dtor_(&prison.stack);
    printf("Stack deleted\n");

    int error = 0;
    Stack_dtor_(&prison.stack, &error);
    // Expected output - !Attention! Stack.data has invalid pointer (code: -4)
    printf("!Attention! %s (code: %d)\n", Stack_error_desc(error), error);

    printf(RED "|--------------------     End of test     --------------------|\n" NATURAL);

    return 0;
}
int error_while_push_test() {
    printf(RED "|-------------------     Start of test     -------------------|\n" NATURAL);
    printf(GREEN "This is test, where something changes stack.capacity from 256 to 270 (can detect with dump log)\n"
                 "If VALIDATE_LEVEL == NO_VALIDATE:   program should end with exit code 0 and variable error = -11\n"
                 "If VALIDATE_LEVEL >= WEAK_VALIDATE: program should fall with SIGABRT    and variable error = -11\n"
                 "                                    Also should be:\n"
                 "                                      1. init dump\n"
                 "                                      2. info about changing capacity\n"
                 "                                      3. dump with error (Stack_error failed in the beginning of push func)\n"
                 "                                    !NOTE! if VALIDATE_LEVEL >= STRONG_VALIDATE variable error should be -13\n"
                 "Program can exit with exit code 0 or fall with SIGABRT\n\n"
           NATURAL);

    DEFINE_STACK;

    int error = 0;
    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        push(&prison.stack, i + 1, &error);
        if (i == CAP_BORDER / 2) {
            prison.left_executioner[24] = 14;
        }
    }

    // Expected output - !Attention! Stack damaged. Something messed stack.data canary (code: -11)
    printf("!Attention! %s (code: %d)\n", Stack_error_desc(error), error);
    if (error) {
        printf(RED "|--------------------     End of test     --------------------|\n" NATURAL);
        return 0;
    }

    // Next code must not be executed
    printf(RED "Oh no... You broke my program...\n"
               "Are you satisfied? Cause I`m not :(\n"
               "You should be ashamed!!!\n"
           NATURAL);
    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        pop(&prison.stack);
    }

    printf("!Attention! %s (code: %d)\n", Stack_error_desc(error), error);

    TYPICAL_ENDING;

    return -1;
}
int error_with_pop_from_empty_stack_test() {
    printf(RED "|-------------------     Start of test     -------------------|\n" NATURAL);
    printf(GREEN "This is test, where user tru to pop from empty stack\n"
                 "If VALIDATE_LEVEL == NO_VALIDATE:   program should end with exit code  -6 and variable error = -6\n"
                 "If VALIDATE_LEVEL >= WEAK_VALIDATE: program should fall with SIGABRT      and variable error = -6\n"
                 "                                    Also should be:\n"
                 "                                      1. init dump\n"
                 "                                      2. info about changing capacity\n"
                 "                                      3. dump with error (Cannot pop from empty stack)\n"
                 "                                    !NOTE! if VALIDATE_LEVEL >= STRONG_VALIDATE variable error should be -13\n"
                 "Program can exit with exit code -6 or fall with SIGABRT\n\n"
           NATURAL);

    DEFINE_STACK;

    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        push(&prison.stack, i + 1);
    }

    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        pop(&prison.stack);
    }

    printf("And now program should fall!\n");
    int error = 0;
    pop(&prison.stack, &error);

    // Expected output - !Attention! Stack is empty (code: -6)
    printf("!Attention! %s (code: %d)\n", Stack_error_desc(error), error);
    if (error) {
        printf(RED "|--------------------     End of test     --------------------|\n" NATURAL);
        return 0;
    }

    // Next code must not be executed
    printf(RED "Oh no... You broke my program...\n"
               "Are you satisfied? Cause I`m not :(\n"
               "You should be ashamed!!!\n"
           NATURAL);

    TYPICAL_ENDING;

    return -1;
}
int error_with_damaged_canary_test() {
    printf(RED "|-------------------     Start of test     -------------------|\n" NATURAL);
    printf(GREEN "This is test, where someone damaged stack canary\n"
                 "If VALIDATE_LEVEL == NO_VALIDATE:   program should end with exit code   0 and variable error = -10\n"
                 "If VALIDATE_LEVEL >= WEAK_VALIDATE: program should fall with SIGABRT      and variable error = -10\n"
                 "                                    Also should be:\n"
                 "                                      1. init dump\n"
                 "                                      2. info about changing capacity\n"
                 "                                      3. dump with error (Stack_error failed in the beginning of pop func)\n"
                 "Program can exit with exit code 0 or fall with SIGABRT\n\n"
                 NATURAL);

    DEFINE_STACK;

    for (int i = 0; i < CAP_BORDER / 2; i++) {
        push(&prison.stack, i + 1);
    }

    prison.left_executioner[10] = 13;

    int error = 0;
    for (int i = 0; i < CAP_BORDER / 2; i++) {
        pop(&prison.stack, &error);
    }

    // Expected output - !Attention! Stack damaged. Something messed stack canary (code: -10)
    printf("!Attention! %s (code: %d)\n", Stack_error_desc(error), error);
    if (error) {
        printf(RED "|--------------------     End of test     --------------------|\n" NATURAL);
        return 0;
    }

    // Next code must not be executed
    printf(RED "Oh no... You broke my program...\n"
               "Are you satisfied? Cause I`m not :(\n"
               "You should be ashamed!!!\n"
           NATURAL);

    TYPICAL_ENDING;

    return -1;
}
int error_with_invalid_data_ptr_test() {
    printf(RED "|-------------------     Start of test     -------------------|\n" NATURAL);
    printf(GREEN "This is test, where someone changes data.stack pointer\n"
                 "If VALIDATE_LEVEL == NO_VALIDATE:   program should end with exit code   0 and variable error = -4\n"
                 "If VALIDATE_LEVEL >= WEAK_VALIDATE: program should fall with SIGABRT      and variable error = -4\n"
                 "                                    Also should be:\n"
                 "                                      1. init dump\n"
                 "                                      2. info about changing capacity\n"
                 "                                      3. dump with error (Stack_error failed in the beginning of pop func)\n"
                 "Program can exit with exit code 0 or fall with SIGABRT\n\n"
           NATURAL);

    DEFINE_STACK;

    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        push(&prison.stack, i + 1);
    }

    prison.left_executioner[22] = 13;

    int error = 0;
    for (int i = 0; i < CAP_BORDER + 6 * CAP_STEP + 50; i++) {
        pop(&prison.stack, &error);
    }

    // Expected output - !Attention! Stack damaged. Something messed stack canary (code: -10)
    printf("!Attention! %s (code: %d)\n", Stack_error_desc(error), error);
    if (error) {
        printf(RED "|--------------------     End of test     --------------------|\n" NATURAL);
        return 0;
    }

    // Next code must not be executed
    printf(RED "Oh no... You broke my program...\n"
               "Are you satisfied? Cause I`m not :(\n"
               "You should be ashamed!!!\n"
           NATURAL);

    TYPICAL_ENDING;

    return -1;
}
