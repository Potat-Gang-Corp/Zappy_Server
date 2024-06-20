/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** spell_cmd
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

int cmd_broadcast(char *command_type, int cli_socket)
{
    char *msg_without_prefix = strstr(command_type, "Broadcast ");
    client_t *cli = get_client_by_socket(cli_socket);

    if (!msg_without_prefix) {
        dprintf(cli_socket, "ko\n");
        return 84;
    }
    msg_without_prefix += strlen("Broadcast ");
    sending_message(cli, msg_without_prefix);
    cli->cd = 7 / get_game_instance()->freq;
    return 0;
}

void notice_graphic_client_fork_begin(client_t *cli)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->graphic == true) {
            dprintf(graphic->socket, "pfk #%d\n", cli->socket);
        }
    }
}

int cmd_fork(char *command_type, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);
    game_t *game = get_game_instance();

    (void)command_type;
    for (int j = 0; j < game->nb_teams; j++) {
        if (strcmp(game->teams[j]->name, cli->team) == 0) {
            cli->egg_id_laying = game->nb_eggs_layed;
            game->nb_eggs_layed++;
            cli->is_laying = true;
        }
    }
    cli->cd = 42 / game->freq;
    notice_graphic_client_fork_begin(cli);
    dprintf(cli_socket, "ok\n");
    return 0;
}

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
    if (cpt == nb) {
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
        if (current_items[i] == requirements[i]) {
            items_present |= 1 << i;
        }
    }
    return (items_present == 0x3F);
}


void get_items_on_tile(int x, int y, elevation_requirements_t **elevation_tab)
{
    map_t *map = get_map_instance();
    int index = x + y * map->width;
    items_t *items = map->tiles[index]->items;

    while(items) {
        if (items->type == LINEMATE) {
            (*elevation_tab)->linemate++;
        } else if (items->type == DERAUMERE) {
            (*elevation_tab)->deraumere++;
        } else if (items->type == SIBUR) {
            (*elevation_tab)->sibur++;
        } else if (items->type == MENDIANE) {
            (*elevation_tab)->mendiane++;
        } else if (items->type == PHIRAS) {
            (*elevation_tab)->phiras++;
        } else if (items->type == THYSTAME) {
            (*elevation_tab)->thystame++;
        }
        items = items->next;
    }
}

int check_condition_incantation(client_t *cli)
{
    elevation_requirements_t *elevation_tab = NULL;

    get_items_on_tile(cli->pos.x, cli->pos.y, &elevation_tab);
    if (compare_structs(elevation_tab, cli->level) == false) {
        return 0;
    }
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

int cmd_incantation(char *command_type, int cli_socket)
{
    (void)command_type;
    client_t *cli = get_client_by_socket(cli_socket);
    
    if (check_condition_incantation(cli) == 0) {
        dprintf(cli_socket, "ko\n");
        return 84;
    }
    dprintf(cli_socket, "Elevation underway\n");
    set_bool_incantation(cli->pos.x, cli->pos.y, cli->level);
    cli->cd = 300 / get_game_instance()->freq;
    cli->evolving = true;
    return 0;
}
