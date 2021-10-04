//
// Created by ivanbrekman on 04.10.2021.
//

#ifndef STACK_TEST_H
#define STACK_TEST_H

#include "../config.h"

struct Prison {
    char left_executioner[1];
    Stack stack;
    char right_executioner[1];
};

int is_stack_broken_test(Stack* stack);

int normal_work_test();
int error_with_second_dtor_call_test();
int error_while_push_test();
int error_with_pop_from_empty_stack_test();
int error_with_damaged_canary_test();
int error_with_invalid_data_ptr_test();

#endif //STACK_TEST_H
