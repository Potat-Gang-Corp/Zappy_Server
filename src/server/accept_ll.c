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
int init_ll_error_handling(int new_socket)
{
    server_t *server = get_instance();
    game_t *game = get_game_instance();

    if (server == NULL) {
        fprintf(stderr, "Error: server instance is NULL\n");
        close(new_socket);
        return 84;
    }
    if (game == NULL) {
        fprintf(stderr, "Error: game instance is NULL\n");
        close(new_socket);
        return 84;
    }
    return 0;
}

int init_ll(int new_socket, int index)
{
    server_t *server = get_instance();
    game_t *game = get_game_instance();

    if (init_ll_error_handling(new_socket) == 84)
        return 84;
    if (index < 0 || index >= game->nb_teams) {
        fprintf(stderr, "Error: invalid index %d\n", index);
        close(new_socket);
        return 84;
    }
    server->clients = malloc(sizeof(client_t));
    if (server->clients == NULL) {
        perror("malloc");
        close(new_socket);
        return 84;
    }
    server->clients->socket = new_socket;
    server->clients->team = game->teams[index]->name;
    server->clients->next = NULL;
    return 0;
}

int add_to_ll_bis(int new_socket, int index)
{
    server_t *server = get_instance();
    game_t *game = get_game_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli->next; cli = cli->next);
    cli->next = malloc(sizeof(client_t));
    if (cli->next == NULL) {
        perror("malloc");
        close(new_socket);
        return 84;
    }
    cli->next->socket = new_socket;
    cli->next->team = game->teams[index]->name;
    cli->next->next = NULL;
    return 0;
}

int add_to_ll(int new_socket, int index)
{
    server_t *server = get_instance();

    if (server->clients == NULL) {
        if (init_ll(new_socket, index) == 84) {
            fprintf(stderr, "Error: can't init linked list\n");
            return 84;
        }
    } else {
        if (add_to_ll_bis(new_socket, index) == 84) {
            fprintf(stderr, "Error: can't add to linked list\n");
            return 84;
        }
    }
    return 0;
}

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
