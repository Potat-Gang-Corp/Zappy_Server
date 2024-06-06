/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** accept_ll
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"

/**
* @file accept_ll.c
* @brief contains functions for the linked lists
*/

int add_to_waiting_list(int new_socket, const char *team)
{
    server_t *server = get_instance();
    waiting_client_t *new_waiting_client = malloc(sizeof(waiting_client_t));

    if (new_waiting_client == NULL) {
        perror("malloc");
        close(new_socket);
        return 84;
    }
    new_waiting_client->socket = new_socket;
    new_waiting_client->team = strdup(team);
    if (new_waiting_client->team == NULL) {
        perror("strdup");
        close(new_socket);
        free(new_waiting_client);
        return 84;
    }
    TAILQ_INSERT_TAIL(&server->waiting_list, new_waiting_client, entries);
    return 0;
}
