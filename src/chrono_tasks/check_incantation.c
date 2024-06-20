/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** check_incantation
*/

#include "server.h"
#include "get_instance.h"
#include "elevation.h"

void set_level(int x, int y, int lvl)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;

    for (; cli != NULL; cli = cli->next) {
        if (cli->pos.x == x && cli->pos.y == y 
            && cli->level == (unsigned int)lvl && cli->is_incanting == true) {
            cli->level++;
            cli->is_incanting = false;
        }
    }
}

void check_conditions(client_t *cli)
{
    if (cli->is_incanting == true && cli->cd > 0) {
        return;
    } else if (cli->is_incanting == true && cli->cd == 0) {
        if (cli->evolving == true) {
            set_level(cli->pos.x, cli->pos.y, cli->level);
            cli->is_incanting = false;
            cli->level++;
        }
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
