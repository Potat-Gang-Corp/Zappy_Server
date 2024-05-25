/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** select_cli
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"

static int select_function()
{
    struct server_s *server = get_instance();
    //revoir select
    if (select(server->maxfd + 1, &server->readfs, &server->writefds,
        NULL, NULL) < 0) {
        perror("select");
        return 84;
    }
    return 0;
}

int select_loop(void)
{
    struct server_s *server = get_instance();
    client_t *cli = NULL;

    FD_ZERO(&server->readfs); //on initialise le readfs
    FD_ZERO(&server->writefds); //on initialise le writefds
    FD_SET(server->socket, &server->readfs); //on ajoute le socket dans le readfs
    server->maxfd = server->socket;
    for (cli = server->clients; cli; cli = cli->next) {
        if (cli->socket > 0) { 
            FD_SET(cli->socket, &server->readfs); //on ajoute le client dans le readfs
            FD_SET(cli->socket, &server->writefds); //on ajoute le client dans le writefds
        }
        if (cli->socket > server->maxfd)
            server->maxfd = cli->socket;
    }
    if (select_function() == 84) {
        fprintf(stderr, "Error: In the select can't launch server\n");
        return 84;
    }
    return 0;
}
