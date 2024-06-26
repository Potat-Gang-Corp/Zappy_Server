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

int calc_len_ll(client_t *clients)
{
    int len = 0;

    while (clients) {
        if (clients->graphic == false)
            len++;
        clients = clients->next;
    }
    return len;
}

int handle_socket_error(void)
{
    if (errno == EMFILE || errno == ENFILE) {
        fprintf(stderr, "Too many open files. Cannot accept new client.\n");
    } else {
        perror("accept");
    }
    return 84;
}

int accept_new_client(void)
{
    server_t *server = get_instance();
    int new_socket = 0;
    int len_ll = calc_len_ll(server->clients);

    printf("Accepting new client\n");
    if (FD_ISSET(server->socket, &server->readfs)) {
        if (len_ll >= MAX_CLIENTS) {
            fprintf(stderr, "Server is full\n");
            return 0;
        }
        new_socket = accept(server->socket, NULL, NULL);
        if (new_socket < 0) {
            return handle_socket_error();
        }
        if (add_client(new_socket) == 84) {
            close(new_socket);
            return 84;
        }
    }
    return 0;
}
