/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_main
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
int add_func(int a, int b);

Test(add_func, return_type)
{
    cr_assert_eq(add_func(1, 2), 3);
}
