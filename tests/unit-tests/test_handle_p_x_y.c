/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_n_c_f flags
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/handle_flags.h"

Test(handle_p, test_handle_x_function)
{
    char *invalid_buffer = "abc";
    char *negative_value = "-1";
    char *valid_value = "8080";
    char *invalid_value = "66666";
    char *letter_and_digits = "80a80";
    cr_assert_eq(handle_p(invalid_buffer), 84, "Expected exit code 84 for char value : %s", invalid_buffer);
    cr_assert_eq(handle_p(negative_value), 84, "Expected exit code 84 for negative value : %s", negative_value);
    cr_assert_eq(handle_p(valid_value), 0, "Expected exit code 0 for a value greater than 0 and less than 65535 : %s", valid_value);
    cr_assert_eq(handle_p(invalid_value), 84, "Expected exit code 84 for a value greater than 65535 : %s", invalid_value);
    cr_assert_eq(handle_p(letter_and_digits), 84, "Expected exit code 84 for a string that contains digits and letter : %s", letter_and_digits);
}

Test(handle_x, test_handle_x_function)
{
    char *invalid_buffer = "abc";
    char *negative_value = "-1";
    char *inferior_value = "4";
    char *valid_value = "5";
    cr_assert_eq(handle_x(invalid_buffer), 84, "Expected exit code 84 for char value : %s", invalid_buffer);
    cr_assert_eq(handle_x(negative_value), 84, "Expected exit code 84 for negative value : %s", negative_value);
    cr_assert_eq(handle_y(negative_value), 84, "Expected exit code 84 for inferior value : %s", inferior_value);
    cr_assert_eq(handle_x(valid_value), 0, "Expected exit code 0 for positive value : %s", valid_value);
}

Test(handle_y, test_handle_y_function)
{
    char *invalid_buffer = "abc";
    char *negative_value = "-1";
    char *inferior_value = "4";
    char *valid_value = "5";
    cr_assert_eq(handle_y(invalid_buffer), 84, "Expected exit code 84 for char value : %s", invalid_buffer);
    cr_assert_eq(handle_y(negative_value), 84, "Expected exit code 84 for negative value : %s", negative_value);
    cr_assert_eq(handle_y(negative_value), 84, "Expected exit code 84 for inferior value : %s", inferior_value);
    cr_assert_eq(handle_y(valid_value), 0, "Expected exit code 0 for positive value : %s", valid_value);
}

Test(handle_x_y, test_handle_x_y_function)
{
    char *no_valid_x_def[13] = {"./zappy_server", "-p", "8080", "-x", "a", "-y", "10", "-n", "the", "potato", "group", "-c", "10"};
    char *valid_x_def[13] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "10", "-n", "the", "potato", "group", "-c", "10"};
    char *no_valid_y_def[13] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "a", "-n", "the", "potato", "group", "-c", "10"};
    char *valid_y_def[13] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "10", "-n", "the", "potato", "group", "-c", "10"};
    int i = 3;
    int fp = 0;

    cr_assert_eq(handle_x_y(12, &i, no_valid_x_def, &fp), 84, "Expected exit code 84 because no valid definition for x parameter");

    i = 3;
    fp = 0;

    cr_assert_eq(handle_x_y(12, &i, valid_x_def, &fp), 0, "Expected exit code 0 because valid definition for x parameter");

    i = 5;
    fp = 0;

    cr_assert_eq(handle_x_y(12, &i, no_valid_y_def, &fp), 84, "Expected exit code 84 because no valid definition for y parameter");

    i = 5;
    fp = 0;

    cr_assert_eq(handle_x_y(12, &i, valid_y_def, &fp), 0, "Expected exit code 0 because valid definition for x parameter");
}
