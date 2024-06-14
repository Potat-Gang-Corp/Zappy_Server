/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_move_cmd
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

// Test moving player north
Test(player_movement, move_player_north) {
    game_t game = {.width = 10, .height = 10};
    client_t client = {.pos = {.x = 5, .y = 5, .orientation = NORTH}};

    move_player(&client, &game);
    cr_assert_eq(client.pos.y, 4, "Client should move north (y decremented by 1).");
    cr_assert_eq(client.pos.x, 5, "Client x-coordinate should remain unchanged.");
}

// Test moving player south
Test(player_movement, move_player_south) {
    game_t game = {.width = 10, .height = 10};
    client_t client = {.pos = {.x = 5, .y = 5, .orientation = SOUTH}};

    move_player(&client, &game);
    cr_assert_eq(client.pos.y, 6, "Client should move south (y incremented by 1).");
    cr_assert_eq(client.pos.x, 5, "Client x-coordinate should remain unchanged.");
}

// Test moving player east and wrapping around
Test(player_movement, move_player_east_wrap_around) {
    game_t game = {.width = 10, .height = 10};
    client_t client = {.pos = {.x = 9, .y = 5, .orientation = EAST}};

    move_player(&client, &game);
    cr_assert_eq(client.pos.x, 0, "Client should move east and wrap around (x set to 0).");
    cr_assert_eq(client.pos.y, 5, "Client y-coordinate should remain unchanged.");
}

// Test moving player west and wrapping around
Test(player_movement, move_player_west_wrap_around) {
    game_t game = {.width = 10, .height = 10};
    client_t client = {.pos = {.x = 0, .y = 5, .orientation = WEST}};

    move_player(&client, &game);
    cr_assert_eq(client.pos.x, 9, "Client should move west and wrap around (x set to 9).");
    cr_assert_eq(client.pos.y, 5, "Client y-coordinate should remain unchanged.");
}

