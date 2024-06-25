/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** map
*/

#ifndef EGG_H
    #define EGG_H

void place_egg_on_map_bis(int team_index, map_t *map);
void add_egg_to_team_ll(team_t *team, int x, int y, int egg_id);

void handle_egg_laying(void);
void destroy_eggs(egg_t *egg, int x, int y);
void delete_egg(egg_t **egg, egg_t **prev_egg, egg_t **curr_egg);

#endif //EGG_H
