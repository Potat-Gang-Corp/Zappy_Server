/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** accept_cli
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"

/**
* @file accept_cli.c
* @brief accept protocol for the server
*/

int accept_loop(int new_socket, int nb_joueur, int index)
{
    game_t *game = get_game_instance();

    if (!(nb_joueur >= 1 || game->teams[index]->cpt_egg > 0)) {
        if (add_to_waiting_list(new_socket, game->teams[index]->name) == 84) {
            fprintf(stderr, "Error: can't add to waiting list\n");
            return 84;
        }
    } else {
        if (add_to_ll(new_socket, index) == 84) {
            fprintf(stderr, "Error: can't add to linked list\n");
            return 84;
        }
    }
    return 0;
}

void define_client_parameters(client_t *new_client, int client_socket)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    new_client->socket = client_socket;
    new_client->team = NULL;
    new_client->status = false;
    new_client->nb_commands = 0;
    new_client->next = NULL;
    if (server->clients == NULL) {
        server->clients = new_client;
    } else {
        cli = server->clients;
        while (cli->next != NULL){
            cli = cli->next;
        }
        cli->next = new_client;
    }
}

int add_client(int client_socket)
{
    client_t *new_client = malloc(sizeof(client_t));

    if (new_client == NULL) {
        perror("malloc");
        close(client_socket);
        return 84;
    }
    define_client_parameters(new_client, client_socket);
    printf("Added new client with socket %d\n", client_socket);
    write(new_client->socket, "WELCOME\r\n", strlen("WELCOME\r\n"));
    return 0;
}

int accept_new_client(void)
{
    server_t *server = get_instance();
    int new_socket = 0;

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
