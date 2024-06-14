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

#endif /* !MAP_H_ */
