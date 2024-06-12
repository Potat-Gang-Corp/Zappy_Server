/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_command_reception
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"
#include <time.h>

Test(parse_command_tests, normal_command)
{
    char input[] = "Forward 12 \n";
    char *expected = "Forward 12 ";
    char *result = parse_command(input);
    cr_assert_str_eq(result, expected, "Expected '%s' but got '%s'", expected, result);
}

Test(parse_command_tests, empty_command)
{
    char input[] = "\n";
    char *result = parse_command(input);
    cr_assert_null(result);
}

Test(parse_command_tests, no_newline_character)
{
    char input[] = "Forward 12 ";
    char *expected = "Forward 12 ";
    char *result = parse_command(input);
    cr_assert_str_eq(result, expected, "Expected '%s' but got '%s'", expected, result);
}
