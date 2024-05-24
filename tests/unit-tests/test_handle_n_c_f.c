/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_map
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../../include/handle_flags.h"

Test(handle_n, test_handle_c_function) {
    int fp = 0;
    char *null_array
}

Test(handle_c, test_handle_c_function) {
    int fp = 0;
    char *invalid_buffer = "abc";
    char *negative_value = "-1";
    char *valid_value = "1";
    cr_assert_eq(handle_c(invalid_buffer, &fp), 84, "Expected exit code 84 for char value");
    cr_assert_eq(handle_c(negative_value, &fp), 84, "Expected exit code 84 for negative value");
    cr_assert_eq(handle_c(valid_value, &fp), 0, "Expected exit code 0 for positive value");
}


Test(handle_f, test_handle_f_function) {
    int fp = 0;
    char *invalid_buffer = "abc";
    char *negative_value = "-1";
    char *valid_value = "1";
    cr_assert_eq(handle_f(invalid_buffer, &fp), 84, "Expected exit code 84 for char value");
    cr_assert_eq(handle_f(negative_value, &fp), 84, "Expected exit code 84 for negative value");
    cr_assert_eq(handle_f(valid_value, &fp), 0, "Expected exit code 0 for positive value");
}

