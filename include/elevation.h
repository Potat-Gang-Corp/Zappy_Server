/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** elevation
*/

#ifndef ELEVATION_H_
    #define ELEVATION_H_

    #include "struct_client.h"

typedef struct elevation_requirements_s {
    int nb_players;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} elevation_requirements_t;

int check_condition_incantation(client_t *cli);
void set_bool_incantation(int level, int x, int y);
void get_items_on_tile(int x, int y, elevation_requirements_t *elevation_tab);
bool compare_structs(elevation_requirements_t *elevation_tab, int level);
bool check_level_players(client_t *s, int level, int nb);
void increment_item(elevation_requirements_t *lvl_tab, item_type_t type);

extern const elevation_requirements_t elevation_table[];

#endif /* !ELEVATION_H_ */
