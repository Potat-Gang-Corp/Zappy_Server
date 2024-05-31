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
    struct timeval timeout;

    timeout.tv_sec = 300;
    timeout.tv_usec = 0;
    if (select(server->maxfd + 1, &server->readfs, &server->writefds,
        NULL, &timeout) < 0 && (errno != EINTR)) {
        perror("select");
        return 84;
    }
    return 0;
}



int select_loop(void)
{
    server_t *server = get_instance();
    waiting_client_t *cli = NULL;

    FD_ZERO(&server->readfs);
    FD_ZERO(&server->writefds);
    FD_SET(server->socket, &server->readfs);  // Listening socket
    server->maxfd = server->socket;

    TAILQ_FOREACH(cli, &server->waiting_list, entries) {
        if (cli->socket > 0) {
            FD_SET(cli->socket, &server->readfs);
            FD_SET(cli->socket, &server->writefds);
            if (cli->socket > server->maxfd) {
                server->maxfd = cli->socket;
            }
        }
    }

    if (select_function() == 84) {
        fprintf(stderr, "Error in select_function()\n");
        return 84;
    }
    return 0;
}
