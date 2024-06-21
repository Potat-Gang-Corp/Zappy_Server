/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** chrono_function
*/

#include "server.h"
#include "get_instance.h"
#include "commands_gui.h"
#include "elevation.h"

void execute_chrono_tasks(void)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->logged == false)
            continue;
        if (cli->graphic == true)
            cmd_mct("mct", cli->socket);
        if (!(cli->graphic == true)) {
            lower_cli_cd(cli);
            handle_player_death(cli);
        }
    }
    handle_end_game();
    handle_timeout_login();
    handle_egg_laying();
    handle_renew_items();
    handle_incantation();
}
