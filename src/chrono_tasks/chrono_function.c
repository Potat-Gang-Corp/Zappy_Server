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

void handle_exec_chrono_task_bis(void)
{
    handle_end_game();
    handle_timeout_login();
    handle_egg_laying();
    handle_renew_items();
    handle_incantation();
}

void execute_chrono_tasks(void)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;
    client_t *next_cli;

    while (cli != NULL) {
        next_cli = cli->next;
        if (!cli->logged) {
            cli = next_cli;
            continue;
        }
        if (cli->graphic) {
            cmd_mct("mct", cli->socket);
        } else {
            lower_cli_cd(cli);
            handle_player_death(cli);
        }
        cli = next_cli;
    }
}
