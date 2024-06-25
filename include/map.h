/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include "struct_map.h"

void delete_item_from_tiles(tile_t *tile, item_type_t type);
int checking_item_existence(items_t *item, item_type_t type);
void add_egg_to_team_ll(team_t *team, int x, int y, int egg_id);

void second_init_map(map_t *map, int x, int y, int width);
void init_map(map_t *map, int width, int height);
int initialize_map(int width, int height);
void display(struct map_s *map);

int place_mendiane_on_map(map_t *map);
int place_sibur_on_map(map_t *map);
int place_deraumere_on_map(map_t *map);
int place_linemate_on_map(map_t *map);
int place_food_on_map(map_t *map);

int place_phiras_on_map(map_t *map);
int place_thystame_on_map(map_t *map);

const char *get_food(void);
const char *get_linemate(void);
const char *get_deraumere(void);
const char *get_sibur(void);
const char *get_mendiane(void);
const char *get_phiras(void);
const char *get_thystame(void);
const char *get_egg(void);
const char *get_player(void);
const char *get_unknown(void);

void add_item_to_tiles(tile_t *tile, item_type_t type);
void place_randomly_items(map_t *map);
const char *get_items(item_type_t item);
item_type_t get_item_type(const char *item_name);
void delete_item_from_tiles(tile_t *tile, item_type_t type);
int checking_item_existence(items_t *item, item_type_t type);
void handle_renew_items(void);
void refill_deraumere(map_t *map, int *counter_items);
void refill_linemate(map_t *map, int *counter_items);
void refill_food(map_t *map, int *counter_items);
void count_items_on_map(int *counter_items, tile_t *tile);
void refill_mendiane(map_t *map, int *counter_items);
void refill_phiras(map_t *map, int *counter_items);
void refill_thystame(map_t *map, int *counter_items);
void handle_renew_items_bis(map_t *map, int *counter_items);
void refill_sibur(map_t *map, int *counter_items);
void push_players_to_tile(client_t *cli, int x, int y);

#endif /* !MAP_H_ */
