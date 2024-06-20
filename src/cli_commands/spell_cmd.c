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

//this neither

// static const uint32_t elevation_table[EGG][7] = {
//     { 0, 1, 0, 0, 0, 0, 0 },
//     { 0, 1, 1, 1, 0, 0, 0 },
//     { 0, 2, 0, 1, 0, 2, 0 },
//     { 0, 1, 1, 2, 0, 1, 0 },
//     { 0, 1, 2, 1, 3, 0, 0 },
//     { 0, 1, 2, 3, 0, 1, 0 },
//     { 0, 2, 2, 2, 2, 2, 1 }
// };

// static const int new_player_elevation_table[7] = {
//     0,
//     1,
//     0,
//     1,
//     0,
//     1,
//     0,
// };

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

void get_nb_players_in_tile(client_t *cli, int *nb_players)
{
    server_t *server = get_instance();
    client_t *tmp = NULL;

    for (tmp = server->clients; tmp != NULL; tmp = tmp->next) {
        if (tmp->pos.x == cli->pos.x && tmp->pos.y == cli->pos.y && tmp->level >= cli->level)
            nb_players[0]++;
    }
}

void get_char_counter_username(client_t *cli, int *char_count)
{
    server_t *server = get_instance();
    client_t *tmp = NULL;
    int user_counter = 0;

    char_count[0] += snprintf(NULL, 0, "#%d ", cli->socket);
    for (tmp = server->clients; tmp != NULL && user_counter  < new_player_elevation_table[cli->level - 1] - 1; tmp = tmp->next) {
        if (tmp->pos.x == cli->pos.x && tmp->pos.y == cli->pos.y && tmp->level >= cli->level && tmp->socket != cli->socket) {
            char_count[0] += snprintf(NULL, 0, "#%d ", tmp->socket);
            user_counter++;
        }
    }
    return char_count[0];
}

char *build_username_message(client_t *cli, char *username)
{
    server_t *server = get_instance();
    client_t *tmp = NULL;

    strcat(username, "#");
    strcat(username, my_itoa(cli->socket));

    for (tmp = server->clients; tmp != NULL; tmp = tmp->next) {
        if (tmp->pos.x == cli->pos.x && tmp->pos.y == cli->pos.y && tmp->level >= cli->level && tmp->socket != cli->socket) {
            strcat(username, " #");
            strcat(username, my_itoa(tmp->socket));
        }
    }
    return username;
}

static void evolve_level_two(client_t *cli)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;
    client_t *tmp = NULL;
    char *msg = NULL;
    int char_count = 0;
    //j'aime pas
    // int inventory_items[] = {
    //     cli->inventory.food,
    //     cli->inventory.linemate,
    //     cli->inventory.deraumere,
    //     cli->inventory.sibur,
    //     cli->inventory.mendiane,
    //     cli->inventory.phiras,
    //     cli->inventory.thystame
    // };

    for (int i = 0; i < EGG; i++) {
        if (inventory_items[i] < elevation_table[cli->level - 1][i]) {
            dprintf(cli->socket, "ko\n");
            return;
        }
    }

    int nb_players = 0;
    get_nb_players_in_tile(cli, &nb_players);
    if (nb_players < new_player_elevation_table[cli->level - 1]) {
        dprintf(cli->socket, "ko\n");
        return;
    }

    char_count += snprintf(NULL, 0, "pic %d %d %d \n", cli->pos.x, cli->pos.y, cli->level + 1, cli->socket);
    char_count += char_count_username(cli, &char_count);

    msg = malloc(sizeof(char) * (char_count + 1));
    msg = build_username_message(cli, msg);

    cli->inventory.food -= elevation_table[cli->level - 1][0];
    cli->inventory.linemate -= elevation_table[cli->level - 1][1];
    cli->inventory.deraumere -= elevation_table[cli->level - 1][2];
    cli->inventory.sibur -= elevation_table[cli->level - 1][3];
    cli->inventory.mendiane -= elevation_table[cli->level - 1][4];
    cli->inventory.phiras -= elevation_table[cli->level - 1][5];
    cli->inventory.thystame -= elevation_table[cli->level - 1][6];

    cli->level++;
    dprintf(cli->socket, "Elevation underway\nCurrent Level:%d\n", cli->level);
    cli->cd = 300 / get_game_instance()->freq;
    cli->is_incanting = true;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->graphic == true) {
            dprintf(graphic->socket, "pic %d %d %d %s\n", cli->pos.x, cli->pos.y, cli->level, msg);
        }
    }

}

int cmd_incantation(char *command_type, int cli_socket)
{
    (void)command_type;
    client_t *cli = get_client_by_socket(cli_socket);
    if (cli->level == 1)
        evolve_level_two(cli);
    return 0;
}
