/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** clean_game_data
*/

#include "../../include/my.h"
#include "../../include/struct_game.h"
#include "../../include/server.h"
#include "../../include/get_instance.h"

void clean_client_struct(void)
{
    server_t *server = get_instance();
    client_t *current_cli = server->clients;
    client_t *client_node = NULL;
    client_t *next_client = NULL;

    while (current_cli != NULL) {
        next_client = current_cli->next;
        client_node = current_cli;
        if (current_cli->team != NULL) {
            free(current_cli->team);
        }
        if (client_node != NULL) {
            free(client_node);
        }
        current_cli = next_client;
    }
    if (current_cli != NULL) {
        free(current_cli);
    }
}