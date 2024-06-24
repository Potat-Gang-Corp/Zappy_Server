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

void check_egg_layed(client_t *cli)
{
    if (cli->cd == 0 && cli->is_laying == true) {
        cli->is_laying = false;
        client_fork_end(cli);
    }
}

void handle_exec_chrono_task_bis(void)
{
    handle_end_game();
    handle_timeout_login();
    handle_egg_laying();
    handle_renew_items();
    handle_incantation();
}

static void send_mct(client_t *cli)
{
    if (cli->cd >= 20) {
        cli->cd = 0;
        cmd_mct("mct", cli->socket);
    } else {
        cli->cd++;
    }
}

void handle_non_graphic_client(client_t *cli)
{
    bool status;

    lower_cli_cd(cli);
    status = handle_player_death(cli);
    if (status == false) {
        return;
    }
    check_egg_layed(cli);
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
            send_mct(cli);
        } else {
            handle_non_graphic_client(cli);
        }
        cli = next_cli;
    }
    handle_exec_chrono_task_bis();
}
