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

#define BUFFER_SIZE 1024


/**
* @file read_write_cmd.c
* @brief read and write command for the server
*/
int add_command_to_list(int cli_id, const char *cmd)
{
    server_t *server = get_instance();
    command_t *new_command = malloc(sizeof(command_t));

    if (new_command == NULL) {
        perror("malloc");
        return 84;
    }
    new_command->cli_id = cli_id;
    new_command->command = strdup(cmd);
    if (new_command->command == NULL) {
        perror("strdup");
        free(new_command);
        return 84;
    }
    TAILQ_INSERT_TAIL(&server->commands, new_command, entries);
    return 0;
}

int find_socket(int cli_socket, struct client_s *cli, char *cmd)
{
    if (cli->socket == cli_socket) {
        if (cli->nb_commands < 10) {
            add_command_to_list(cli->socket, cmd);
            cli->nb_commands++;
        } else {
            fprintf(stderr, "Client %d has too many commands\n", cli_socket);
            return 84;
        }
    }
    return 0;
}

int handle_cmd(int cli_socket, char *cmd) {
    server_t *server = get_instance();
    waiting_client_t *cli;
    cmd[0] = '\0';

    TAILQ_FOREACH(cli, &server->waiting_list, entries) {
        if (cli->socket == cli_socket) {
            /*if (find_socket(cli_socket, cli, cmd) == 84) {
                return 84;
            }*/
            return 0;
        }
    }
    return 84;
}

int cond_of_loop(int cli_socket, int index) {
    server_t *server = get_instance();
    int val = 0;
    printf("Client socket: %d\n", cli_socket);
    if (cli_socket > 0 && FD_ISSET(cli_socket, &server->readfs)) {
        printf("kisiera\n");
        val = process_cli_cmd(cli_socket, index);
        if (val == 84) {
            fprintf(stderr, "Error: can't process command\n");
            return 84;
        } else if (val == -84) {
            return 0;
        }
    }
    return 0;
}

int handle_clients(void)
{
    printf("Handling clients\n");
    server_t *server = get_instance();
    int cli_socket = 0;
    //client_t *cli = NULL;
    int index = 0;
    waiting_client_t *wait_cli = NULL;
    //int bytes_read = 0;
    //char buffer[BUFFER_SIZE];
    
    /*for (cli = server->waiting_list; cli; cli = cli->next) {
        cli_socket = cli->socket;
        if (cond_of_loop(cli_socket, index) == 84) {
            fprintf(stderr, "Error: can't handle clients\n");
            return 84;
        }
        index++;
    }*/
    
    TAILQ_FOREACH(wait_cli, &server->waiting_list, entries) {
        cli_socket = wait_cli->socket;
        printf("Waiting client socket: %d, team: %s\n", cli_socket, wait_cli->team);
        
        FD_SET(cli_socket, &server->readfs);

        if (cond_of_loop(cli_socket, index) == 84) {
            fprintf(stderr, "Error: can't handle clients\n");
            return 84;
        }
        index++;
    }
    return 0;
}
