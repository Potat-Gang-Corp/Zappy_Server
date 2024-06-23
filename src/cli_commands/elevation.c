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
#include "notifications.h"
#include "elevation.h"

bool check_level_players(client_t *s, int level, int nb)
{
    int cpt = 0;
    int size = nb;
    int *tab = malloc((size + 1) * sizeof(int));

    if (tab == NULL) {
        perror("malloc");
        return false;
    }
    cpt++;
    tab[cpt] = s->id;
    cpt = fill_tab(tab, level, nb, s);
    tab[cpt] = -1;
    if (cpt >= nb) {
        notice_gui_incantation(s->pos.x, s->pos.y, level, tab);
        free(tab);
        return true;
    }
    free(tab);
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
    if (check_level_players(cli, cli->level,
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
