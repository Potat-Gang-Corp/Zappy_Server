/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** select_cli
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"

/**
* @file select_cli.c
* @brief select protocol for the server
*/

int select_function(void)
{
    struct server_s *server = get_instance();
    game_t *game = get_game_instance();
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 1000000 / game->freq;
    if (select(server->maxfd + 1, &server->readfs, &server->writefds,
        NULL, &timeout) < 0 && (errno != EINTR)) {
        perror("select");
        return 84;
    }
    return 0;
}

void insert_new_client(client_t *cli, server_t *server)
{
    if (cli->socket > server->maxfd) {
        server->maxfd = cli->socket;
    }
}

int select_loop(void)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    FD_ZERO(&server->readfs);
    FD_ZERO(&server->writefds);
    FD_SET(server->socket, &server->readfs);
    server->maxfd = server->socket;
    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->socket > 0) {
            FD_SET(cli->socket, &server->readfs);
            FD_SET(cli->socket, &server->writefds);
            insert_new_client(cli, server);
        }
    }
    if (select_function() == 84) {
        return 84;
    }
    return 0;
}
