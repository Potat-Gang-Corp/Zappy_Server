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

int write_msg_to_cli(int new_socket, int player_slots)
{
    game_t *g = get_game_instance();
    char world_dim[1024];
    char res_str[1024];

    snprintf(res_str, sizeof(res_str), "%d\r\n", player_slots);
    if (write(new_socket, res_str, strlen(res_str)) == -1) {
        perror("write");
        return 84;
    }
    snprintf(world_dim, sizeof(world_dim), "%d-%d\r\n", g->width, g->height);
    if (write(new_socket, world_dim, strlen(world_dim)) == -1) {
        perror("write");
        return 84;
    }
    return 0;
}

int following(char *team_name, int new_socket)
{
    game_t *game = get_game_instance();
    int i = 0;
    char *msg = "Wrong team name: ko\r\n";
    int player_slots = -84;
    for (i = 0; i < game->nb_teams; i++)
        if (strcmp(game->teams[i]->name, team_name) == 0) {
            player_slots = game->teams[i]->max_clients;
            break;
        }
    if (player_slots == -84) {
        write(new_socket, msg, strlen(msg));
        printf("Client:%d disconnected from the server\n", new_socket);
        close(new_socket);
        return 84;
    }
    printf("Received command: \"%s\" from Client:%d\n", team_name, new_socket);
    if (write_msg_to_cli(new_socket, player_slots) == 84)
        return 84;
    if (accept_loop(new_socket, player_slots, i) == 84)
        return 84;
    return 0;
}

int com_with_cli(int new_socket)
{
    write(new_socket, "WELCOME\r\n", strlen("WELCOME\r\n"));
    if (add_to_waiting_list(new_socket, "") == 84) {
        fprintf(stderr, "Error: can't add to waiting list\n");
        return 84;
    }
    return 0;
}

void add_client(int client_socket) {
    server_t *server = get_instance();
    waiting_client_t *new_client = malloc(sizeof(waiting_client_t));
    if (!new_client) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_client->socket = client_socket;
    strcpy(new_client->team, "");
    TAILQ_INSERT_TAIL(&server->waiting_list, new_client, entries);
    FD_SET(client_socket, &server->readfs);
    if (client_socket > server->maxfd) {
        server->maxfd = client_socket;
    }
    printf("Added new client with socket %d\n", client_socket);
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
        add_to_waiting_list(new_socket, "");
    }
    return 0;
}
