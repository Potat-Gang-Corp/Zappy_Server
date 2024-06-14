/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_execute_cli_cmd
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

Test(add_egg_to_team_ll, should_add_egg_to_team)
{
    team_t team = {0};
    add_egg_to_team_ll(&team, 1, 2, 3);
    cr_assert_not_null(team.egg);
    cr_assert_eq(team.egg->x_pos, 1);
    cr_assert_eq(team.egg->y_pos, 2);
    cr_assert_eq(team.egg->egg_id, 3);
    free(team.egg); // Don't forget to free the allocated memory
}

Test(place_egg_on_map_bis, should_place_egg_on_map)
{
    map_t map = {10, 10, NULL, NULL};
    map.tiles = malloc(sizeof(tile_t*) * 100);
    for (int i = 0; i < 100; i++) {
        map.tiles[i] = malloc(sizeof(tile_t));
        map.tiles[i]->items = NULL;
    }

    game_t *game = get_game_instance();
    game->player_slots = 1;
    game->teams = malloc(sizeof(team_t*));
    game->teams[0] = malloc(sizeof(team_t));
    game->teams[0]->egg = NULL;

    place_egg_on_map_bis(0, &map);

    bool egg_placed = false;
    for (int i = 0; i < 100; i++) {
        items_t *item = map.tiles[i]->items;
        while (item != NULL) {
            if (item->type == EGG) {
                egg_placed = true;
                break;
            }
            item = item->next;
        }
        if (egg_placed) {
            break;
        }
    }
    cr_assert(egg_placed);

    // Free memory after test
    for (int i = 0; i < 100; i++) {
        free(map.tiles[i]);
    }
    free(map.tiles);
    free(game->teams[0]);
    free(game->teams);
}

Test(place_egg_on_map, should_place_eggs_for_each_team)
{
    map_t map = {10, 10, NULL, NULL};
    map.tiles = malloc(sizeof(tile_t*) * 100);
    for (int i = 0; i < 100; i++) {
        map.tiles[i] = malloc(sizeof(tile_t));
        map.tiles[i]->items = NULL;
    }

    game_t *game = get_game_instance();
    game->nb_teams = 2;
    game->player_slots = 1;
    game->teams = malloc(sizeof(team_t*) * game->nb_teams);
    for (int i = 0; i < game->nb_teams; i++) {
        game->teams[i] = malloc(sizeof(team_t));
        game->teams[i]->egg = NULL;
    }

    place_egg_on_map(&map);

    for (int i = 0; i < game->nb_teams; i++) {
        cr_assert_not_null(game->teams[i]->egg, "No egg was placed for team %d", i);
    }

    // Free memory after test
    for (int i = 0; i < 100; i++) {
        free(map.tiles[i]);
    }
    free(map.tiles);
    for (int i = 0; i < game->nb_teams; i++) {
        free(game->teams[i]);
    }
    free(game->teams);
}
