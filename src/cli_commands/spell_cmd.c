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

int cmd_broadcast(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
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

int cmd_incantation(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    return 0;
}
