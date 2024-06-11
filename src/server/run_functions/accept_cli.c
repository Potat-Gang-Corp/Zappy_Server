/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** accept_cli
*/

#include "../../../include/struct_server.h"
#include "../../../include/get_instance.h"
#include "../../../include/server.h"

/**
* @file accept_cli.c
* @brief accept protocol for the server
*/

int accept_new_client(void)
{
    server_t *server = get_instance();
    int new_socket = 0;

    printf("Accepting new client\n");
    if (FD_ISSET(server->socket, &server->readfs)) {
        new_socket = accept(server->socket, NULL, NULL);
        if (new_socket < 0) {
            perror("accept");
            return 84;
        }
        add_client(new_socket);
    }
    return 0;
}
