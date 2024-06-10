/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_cmd_game_detect
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

Test(game_detection, test_command_recognition)
{
    cr_assert_eq(comp_cmd("Left"), 0, "Left should be recognized with return value 0");
    cr_assert_eq(comp_cmd("Look"), 0, "Look should be recognized with return value 0");
    cr_assert_eq(comp_cmd("Broadcast"), 0, "Broadcast should be recognized with return value 0");
    cr_assert_eq(comp_cmd("Eject"), 0, "Eject should be recognized with return value 0");
    cr_assert_eq(comp_cmd("Take"), 0, "Take should be recognized with return value 0");
    cr_assert_eq(comp_cmd("Set"), 0, "Set should be recognized with return value 0");
    cr_assert_eq(comp_cmd("bidulle"), 1, "bidulle should not be recognized and return value 1");

    cr_assert_eq(comp_cmd_bis("Forward"), 0, "Forward should be recognized with return value 0");
    cr_assert_eq(comp_cmd_bis("Right"), 0, "Right should be recognized with return value 0");
    cr_assert_eq(comp_cmd_bis("Fork"), 0, "Fork should be recognized with return value 0");
    cr_assert_eq(comp_cmd_bis("Incantation"), 0, "Incantation should be recognized with return value 0");
    cr_assert_eq(comp_cmd_bis("Connect_nbr"), 0, "Connect_nbr should be recognized with return value 0");
    cr_assert_eq(comp_cmd_bis("Inventory"), 0, "Inventory should be recognized with return value 0");
    cr_assert_eq(comp_cmd_bis("bidulle"), 1, "bidulle should not be recognized and return value 1");
}
