/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** read_write_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

int handle_team_full_status(client_t *cli, team_t *team, game_t *game, char *team_name) {
    char slots[1024];
    char coordinates[1024];
    int length;

    if (team->max_clients < 1) {
        add_to_waiting_list(cli->socket, team_name);
        write(cli->socket, "This team is full, please waiting\r\n",
              strlen("This team is full, please waiting\r\n"));
        return 0;
    } else {
        team->max_clients -= 1;
        length = snprintf(slots, sizeof(slots), "%d\r\n", team->max_clients);
        write(cli->socket, slots, length);
        length = snprintf(coordinates, sizeof(coordinates),
                          "%d %d\r\n", game->width, game->height);
        write(cli->socket, coordinates, length);
        return 0;
    }
}

int detect_client_waiting(int client_socket)
{
    server_t *server = get_instance();
    waiting_client_t *cli;

    TAILQ_FOREACH(cli, &server->waiting_list, entries) {
        if (cli->socket == client_socket) {
            return 84;
        }
    }
    return 0;
}

int detect_team_validity(char *team_name, client_t *cli) {
    game_t *game = get_game_instance();

    for (int i = 0; i < game->nb_teams; i++) {
        if (strcmp(game->teams[i]->name, team_name) == 0) {
            cli->status = true;
            cli->team = strdup(team_name);
            return handle_team_full_status(cli, game->teams[i], game, team_name);
        }
    }
    return 84;
}

void handle_client_login(client_t *cli, char *command) {
    if (cli->status == false && detect_team_validity(command, cli) == 0) {
        return;
    }
    if (cli->status == false && detect_team_validity(command, cli) == 84) {
        write(cli->socket, "Wrong team name, please try again\r\n",
              strlen("Wrong team name, please try again\r\n"));
        return;
    }
    if (cli->status == true && detect_client_waiting(cli->socket) == 0) {
        write(cli->socket, "Request received, you can continue to play\r\n",
              strlen("Request received, you can continue to play\r\n"));
        return;
    }
    if (cli->status == true && detect_client_waiting(cli->socket) == 84) {
        write(cli->socket, "Please waiting it's not your turn\r\n",
              strlen("Please waiting it's not your turn\r\n"));
        return;
    }
}

void load_profile_and_exec(int cli_socket, char *command)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->socket == cli_socket) {
            handle_client_login(cli, command);
        }
    }
}

void execute_cli_commands() {
    server_t *server = get_instance();
    command_t *cmd;

    TAILQ_FOREACH(cmd, &server->commands, entries) {
        printf("Client ID: %d, Command: %s\n", cmd->cli_id, cmd->command);
        load_profile_and_exec(cmd->cli_id, cmd->command);
    }

    while (!TAILQ_EMPTY(&server->commands)) {
        command_t *cmd_cli = TAILQ_FIRST(&server->commands);
        TAILQ_REMOVE(&server->commands, cmd_cli, entries);
        free(cmd_cli->command);
        free(cmd_cli);
    }
}
