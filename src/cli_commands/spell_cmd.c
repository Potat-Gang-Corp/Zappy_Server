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
#include "broadcast.h"

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
    cli->cd = 7;
    return 0;
}

void notice_graphic_client_fork_begin(client_t *cli)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->graphic == true) {
            dprintf(graphic->socket, "pfk #%d\n", cli->id);
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
    cli->cd = 42;
    notice_graphic_client_fork_begin(cli);
    dprintf(cli_socket, "ok\n");
    return 0;
}

int cmd_incantation(char *command_type, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);

    (void)command_type;
    if (check_condition_incantation(cli) == 0) {
        dprintf(cli_socket, "ko\n");
        return 84;
    }
    dprintf(cli_socket, "Elevation underway\n");
    set_bool_incantation(cli->pos.x, cli->pos.y, cli->level);
    cli->cd = 300;
    cli->evolving = true;
    cli->is_incanting = true;
    return 0;
}
