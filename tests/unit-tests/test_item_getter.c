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

Test(resource_tests, get_phiras_returns_correct_string) {
    cr_assert_str_eq(get_phiras(), "PHIRAS", "get_phiras should return the string 'PHIRAS'");
}

Test(resource_tests, get_thystame_returns_correct_string) {
    cr_assert_str_eq(get_thystame(), "THYSTAME", "get_thystame should return the string 'THYSTAME'");
}

Test(resource_tests, get_egg_returns_correct_string) {
    cr_assert_str_eq(get_egg(), "EGG", "get_egg should return the string 'EGG'");
}

Test(resource_tests, get_player_returns_correct_string) {
    cr_assert_str_eq(get_player(), "PLAYER", "get_player should return the string 'PLAYER'");
}

Test(resource_tests, get_unknown_returns_correct_string) {
    cr_assert_str_eq(get_unknown(), "UNKNOWN", "get_unknown should return the string 'UNKNOWN'");
}