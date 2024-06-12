/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** op_cli_ll
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

/**
* @file op_cli_ll.c
* @brief operations on the linked list of clients
*/

client_t *find_client_and_prev(int cli_socket, client_t **prev_out)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;

    *prev_out = NULL;
    while (cli != NULL) {
        if (cli->socket == cli_socket) {
            return cli;
        }
        *prev_out = cli;
        cli = cli->next;
    }
    return NULL;
}

int remove_found_client(client_t *prev, client_t *cli)
{
    server_t *server = get_instance();

    if (cli == NULL)
        return 0;
    if (prev == NULL) {
        server->clients = cli->next;
    } else {
        prev->next = cli->next;
    }
    close(cli->socket);
    if (cli->team != NULL) {
        free(cli->team);
    }
    free(cli);
    return 0;
}

int remove_client(int cli_socket)
{
    client_t *prev;
    client_t *cli = find_client_and_prev(cli_socket, &prev);

    if (remove_found_client(prev, cli) == 84)
        return 84;
    return 0;
}

static void setup_inventory_cli(client_t **cli)
{
    (*cli)->inventory.food = 10;
    (*cli)->inventory.linemate = 0;
    (*cli)->inventory.deraumere = 0;
    (*cli)->inventory.sibur = 0;
    (*cli)->inventory.mendiane = 0;
    (*cli)->inventory.phiras = 0;
    (*cli)->inventory.thystame = 0;
}

static void setup_cli(client_t **new_client, int client_socket)
{
    game_t *game = get_game_instance();

    (*new_client)->socket = client_socket;
    (*new_client)->team = NULL;
    (*new_client)->logged = false;
    (*new_client)->nb_commands = 0;
    (*new_client)->cd = 0;
    (*new_client)->level = 1;
    (*new_client)->graphic = false;
    (*new_client)->evolving = false;
    (*new_client)->time_to_live = 126 / game->freq;
    (*new_client)->next = NULL;
    setup_inventory_cli(new_client);
}

void add_cli_to_ll(client_t *new_client, int client_socket)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    setup_cli(&new_client, client_socket);
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
    add_cli_to_ll(new_client, client_socket);
    printf("Added new client with socket %d\n", client_socket);
    write(new_client->socket, "WELCOME\n", strlen("WELCOME\n"));
    return 0;
}
