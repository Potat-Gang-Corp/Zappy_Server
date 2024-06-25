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
#include "map.h"

Test(resource_tests, get_phiras_returns_correct_string) {
    cr_assert_str_eq(get_phiras(), "phiras", "get_phiras should return the string 'PHIRAS'");
}

Test(resource_tests, get_thystame_returns_correct_string) {
    cr_assert_str_eq(get_thystame(), "thystame", "get_thystame should return the string 'THYSTAME'");
}

Test(resource_tests, get_egg_returns_correct_string) {
    cr_assert_str_eq(get_egg(), "egg", "get_egg should return the string 'EGG'");
}

Test(resource_tests, get_player_returns_correct_string) {
    cr_assert_str_eq(get_player(), "player", "get_player should return the string 'PLAYER'");
}

Test(resource_tests, get_unknown_returns_correct_string) {
    cr_assert_str_eq(get_unknown(), "unknown", "get_unknown should return the string 'UNKNOWN'");
}