/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** elevation
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"
#include "elevation.h"

static const elevation_requirements_t elevation_table[] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};


bool check_level_players(int x, int y, int level, int nb)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;
    int cpt = 0;

    for (; cli != NULL; cli = cli->next) {
        if (cli->pos.x == x && cli->pos.y == y
            && cli->level == (unsigned int)level) {
            cpt++;
        }
    }
    printf("cpt: %d\n", cpt);
    printf("nb: %d\n", nb);
    if (cpt >= nb) {
        return true;
    }
    return false;
}

bool compare_structs(elevation_requirements_t *elevation_tab, int level)
{
    int items_present = 0;
    const int *requirements = &elevation_table[level - 1].linemate;
    int *current_items = &elevation_tab->linemate;

    for (int i = 0; i < 6; i++) {
        if (current_items[i] >= requirements[i]) {
            items_present |= 1 << i;
        }
    }
    return (items_present == 0x3F);
}

static void increment_item(elevation_requirements_t *lvl_tab, item_type_t type)
{
    int *item_pointers[] = {
        &lvl_tab->linemate,
        &lvl_tab->deraumere,
        &lvl_tab->sibur,
        &lvl_tab->mendiane,
        &lvl_tab->phiras,
        &lvl_tab->thystame
    };

    if (type >= LINEMATE && type <= THYSTAME) {
        (*item_pointers[type - LINEMATE])++;
    }
}

void get_items_on_tile(int x, int y, elevation_requirements_t *elevation_tab)
{
    map_t *map = get_map_instance();
    int index = x + y * map->width;
    items_t *items = map->tiles[index]->items;

    while (items) {
        increment_item(elevation_tab, items->type);
        items = items->next;
    }
}

int check_condition_incantation(client_t *cli)
{
    elevation_requirements_t elevation_tab = {0};

    get_items_on_tile(cli->pos.x, cli->pos.y, &elevation_tab);
    if (compare_structs(&elevation_tab, cli->level) == false) {
        return 0;
    }
    if (cli->level <= 1)
        return 1;
    if (check_level_players(cli->pos.x, cli->pos.y, cli->level,
        elevation_table[cli->level - 1].nb_players) == false) {
        return 0;
    }
    return 1;
}

void set_bool_incantation(int level, int x, int y)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;

    for (; cli != NULL; cli = cli->next) {
        if (cli->pos.x == x && cli->pos.y == y
            && cli->level == (unsigned int)level) {
            cli->is_incanting = true;
        }
    }
}
