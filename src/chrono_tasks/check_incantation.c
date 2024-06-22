/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** check_incantation
*/

#include "server.h"
#include "get_instance.h"
#include "elevation.h"
#include "notifications.h"

void set_level(int x, int y, int lvl, int cli_socket)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;

    for (; cli != NULL; cli = cli->next) {
        if (cli->socket == cli_socket)
            continue;
        if (cli->pos.x == x && cli->pos.y == y
            && cli->level == (unsigned int)lvl && cli->is_incanting == true) {
            cli->level++;
            cli->is_incanting = false;
            dprintf(cli->socket, "Current level: %d\n", cli->level);
        }
    }
}

static void check_evolve(client_t *cli)
{
    if (cli->evolving == true) {
        if (check_condition_incantation(cli) == 0) {
            notice_gui_end_incantation(cli->pos.x, cli->pos.y, 1);
            dprintf(cli->socket, "ko\n");
            return;
        }
        set_level(cli->pos.x, cli->pos.y, cli->level, cli->socket);
        notice_gui_end_incantation(cli->pos.x, cli->pos.y, 0);
        cli->is_incanting = false;
        cli->level++;
        dprintf(cli->socket, "Current level: %d\n", cli->level);
    }
}

void check_conditions(client_t *cli)
{
    if (cli->is_incanting == true && cli->cd > 0) {
        return;
    } else if (cli->is_incanting == true && cli->cd == 0) {
        check_evolve(cli);
    }
}

void handle_incantation(void)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;

    for (; cli != NULL; cli = cli->next) {
        check_conditions(cli);
    }
}
