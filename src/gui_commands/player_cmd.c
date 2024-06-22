/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** player
*/

#include "my.h"
#include "get_instance.h"

int cmd_tna(char *command_type, int gui_socket)
{
    int char_count = 0;
    char *buffer;
    game_t *game = get_game_instance();
    client_t *cli = get_client_by_socket(gui_socket);

    (void)command_type;
    for (int i = 0; i < game->nb_teams; i++) {
        char_count += strlen(game->teams[i]->name);
        char_count += strlen("tna \n");
    }
    buffer = malloc(sizeof(char) * char_count + 1);
    buffer[0] = '\0';
    for (int i = 0; i < game->nb_teams; i++) {
        strcat(buffer, "tna ");
        strcat(buffer, game->teams[i]->name);
        strcat(buffer, "\n");
    }
    dprintf(cli->socket, "%s", buffer);
    return 0;
}

int cmd_ppo(char *command, int gui_socket)
{
    server_t *server = get_instance();
    char *player_nb = strtok(command, " ");
    int socket_nb;
    client_t *cli = get_client_by_socket(gui_socket);

    player_nb = strtok(NULL, " #");
    if (player_nb == NULL) {
        dprintf(gui_socket, "sbp\n");
        return 0;
    }
    socket_nb = atoi(player_nb);
    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (socket_nb == cli->id) {
            dprintf(gui_socket, "ppo #%d %d %d %d\n", cli->id, cli->pos.x,
                cli->pos.y, (cli->pos.orientation + 1));
            return 0;
        }
    }
    return 0;
}

int cmd_plv(char *command, int gui_socket)
{
    server_t *server = get_instance();
    char *player_nb = strtok(command, " ");
    int socket_nb;
    client_t *cli = get_client_by_socket(gui_socket);

    player_nb = strtok(NULL, " #");
    socket_nb = atoi(player_nb);
    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (socket_nb == cli->id) {
            dprintf(gui_socket, "plv #%d %d\n", cli->id, cli->level);
            return 0;
        }
    }
    return 0;
}

int cmd_pin(char *command, int gui_socket)
{
    server_t *server = get_instance();
    client_t *player = NULL;
    char *command_type = strtok(command, " ");
    char *player_nb = strtok(NULL, " #");
    int socket_nb = atoi(player_nb);
    client_t *cli = get_client_by_socket(gui_socket);

    command_type = command_type;
    for (player = server->clients; player != NULL; player = player->next) {
        if (socket_nb == player->id) {
            dprintf(cli->socket, "pin #%d %d %d %d %d %d %d %d %d %d\n",
                player->id, player->pos.x, player->pos.y,
                player->inventory.food, player->inventory.linemate,
                player->inventory.deraumere, player->inventory.sibur,
                player->inventory.mendiane, player->inventory.phiras,
                player->inventory.thystame);
            return 0;
        }
    }
    return 0;
}
