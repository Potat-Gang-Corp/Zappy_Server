/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_getter_item
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

Test(append_tests, append_to_empty_string)
{
    char *msg = malloc(1);
    *msg = '\0';
    size_t current_size = 1;

    const char *new_content = "Hello, world!";
    int result = append_to_msg(&msg, &current_size, new_content);

    cr_assert_str_eq(msg, new_content, "The message should match the new content.");
    cr_assert_eq(result, 0, "The function should return 0 on success.");
    cr_assert(current_size > strlen(new_content), "Current size should be greater than the content length.");

    free(msg);
}

Test(append_tests, append_with_reallocation)
{
    char *msg = malloc(5);
    strcpy(msg, "Hi");
    size_t current_size = 5;

    const char *new_content = " there";
    int result = append_to_msg(&msg, &current_size, new_content);

    cr_assert_str_eq(msg, "Hi there", "The message should correctly append new content.");
    cr_assert_eq(result, 0, "The function should return 0 on success.");
    cr_assert(current_size == strlen("Hi") + strlen(new_content) + 1, "Current size should be correctly updated.");

    free(msg);
}

