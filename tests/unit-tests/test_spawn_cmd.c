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
#include "../../include/struct_game.h"
#include "../../include/struct_map.h"
#include <time.h>

Test(game_tests, player_spawn_test_impl) {

    srand(0);

    game_t *game = get_game_instance();
    map_t *map = get_map_instance();

    game->width = 10;
    game->height = 10;
    game->teams = malloc(sizeof(team_t*));
    game->teams[0] = malloc(sizeof(team_t));
    game->teams[0]->egg = malloc(sizeof(egg_t));
    game->teams[0]->egg->x_pos = 5;
    game->teams[0]->egg->y_pos = 5;
    game->teams[0]->egg->next = NULL;

    map->tiles = malloc(game->width * game->height * sizeof(tile_t*));
    for (int i = 0; i < game->width * game->height; i++) {
        map->tiles[i] = malloc(sizeof(tile_t));
        map->tiles[i]->x = i % game->width;
        map->tiles[i]->y = i / game->width;
    }

    client_t client = {0};
    player_spawn(&client, 0);

    cr_assert(client.pos.x == 5 && client.pos.y == 5, "Client should be spawned at egg position.");
    cr_assert(client.pos.orientation >= NORTH && client.pos.orientation <= WEST, "Orientation should be within valid range.");

    for (int i = 0; i < game->width * game->height; i++) {
        free(map->tiles[i]);
    }

}





