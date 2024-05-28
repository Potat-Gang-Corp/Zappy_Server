/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** accept_cli
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"

/**
* @file accept_cli.c
* @brief accept protocol for the server
*/
static int init_ll(int new_socket, int index)
{
    server_t *server = get_instance();
    game_t *game = get_game_instance();

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

static int add_to_ll_bis(int new_socket, int index)
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
}

static int add_to_ll(int new_socket, int index)
{
    server_t *server = get_instance();
    game_t *game = get_game_instance();
    client_t *cli = NULL;

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

static int add_to_waiting_list(int new_socket, const char *team)
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

static int accept_loop(int new_socket, int nb_joueur, int index)
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

static int following(char *team_name, int new_socket)
{
    game_t *game = get_game_instance();
    int player_slots = -84;
    char res_str[1024];
    int i = 0;
    char *msg = "Wrong team name: ko\r\n";

    for (i = 0; i < game->nb_teams; i++)
        if (strcmp(game->teams[i]->name, team_name) == 0)
            player_slots = game->teams[i]->max_clients;
    if (player_slots == -84) {
        write(new_socket, msg, strlen(msg));
        return 84;
    }
    snprintf(res_str, sizeof(res_str), "%d\r\n", player_slots);
    write(new_socket, res_str, strlen(res_str));
    accept_loop(new_socket, player_slots, i);
}

static int com_with_cli(int new_socket)
{
    game_t *game = get_game_instance();
    char *team_name;
    char buffer[1024];
    int bytes_read;

    if ()
    write(new_socket, "WELCOME\r\n", strlen("WELCOME\r\n"));
    bytes_read = read(new_socket, buffer, sizeof(buffer));
    if (bytes_read < 0 && (errno != EAGAIN || errno != EWOULDBLOCK))
        return 84;
    buffer[bytes_read] = '\0';
    if (buffer[0] == '\0')
        new_socket = 0;
    team_name = strtok(buffer, "\r\n");
    following(team_name, new_socket);
}

int accept_new_client(void)
{
    server_t *server = get_instance();
    int new_socket = 0;

    if (FD_ISSET(server->socket, &server->readfs)) {
        new_socket = accept(server->socket, NULL, NULL);
        if (new_socket < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("accept");
            return 84;
        }
        if (com_with_cli(new_socket) == 84) {
            fprintf(stderr, "Error: can't communicate with client\n");
            return 84;
        }
    }
    return 0;
}
