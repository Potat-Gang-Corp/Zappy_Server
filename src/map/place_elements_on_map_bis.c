/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** place_elements_on_map_bis
*/

#include "my.h"
#include "struct_map.h"
#include "get_instance.h"
#include "server.h"

int place_phiras_on_map(map_t *map)
{
    int total_tiles = map->width * map->height;
    int total_phiras = map->width * map->height * 0.2;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_phiras; i++) {
        tile_index = rand() % total_tiles;
        type = PHIRAS;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    return 0;
}

int place_thystame_on_map(map_t *map)
{
    int total_tiles = map->width * map->height;
    int total_thystame = map->width * map->height * 0.1;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_thystame; i++) {
        tile_index = rand() % total_tiles;
        type = THYSTAME;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    return 0;
}

void add_egg_to_team_ll(team_t *team, int x, int y)
{
    egg_t *new_item = malloc(sizeof(egg_t));

    if (!new_item){
        return;
    }
    new_item->x_pos = x;
    new_item->y_pos = y;
    new_item->next = team->egg;
    team->egg = new_item;
}

void place_egg_on_map_bis(int team_index, map_t *map)
{
    game_t *game = get_game_instance();
    int tile_index = 0;
    int x = 0;
    int y = 0;
    item_type_t type;

    for (int j = 0; j < game->player_slots; j++) {
        x = rand() % map->width;
        y = rand() % map->height;
        tile_index = x + y * map->width;
        if (tile_index >= map->width * map->height) {
            continue;
        }
        type = EGG;
        add_item_to_tiles(map->tiles[tile_index], type);
        add_egg_to_team_ll(game->teams[team_index], x, y);
    }
}

int place_egg_on_map(map_t *map)
{
    game_t *game = get_game_instance();

    for (int i = 0; i < game->nb_teams; i++) {
        place_egg_on_map_bis(i, map);
    }
    return 0;
}
