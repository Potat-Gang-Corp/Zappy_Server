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

/**
* @file read_and_print_cmd.c
* @brief read and write command for the server
*/
char *read_cli_cmd(int cli_socket)
{
    printf("Reading command from Client:%d\n", cli_socket);
    char *cmd = malloc(sizeof(char) * (1024 + 1));
    char *parse_command;
    int n = 0;

    if (cmd == NULL)
        return NULL;
    n = read(cli_socket, cmd, 1024);
    if (n < 0) {
        free(cmd);
        perror("read");
        return NULL;
    }
    if (n == 0) {
        free(cmd);
        return NULL;
    }
    cmd[n] = '\0';
    parse_command = strtok(cmd, "\r\n");
    return parse_command;
}

int process_cli_cmd(int cli_socket, int index)
{
    (void) index;
    char *cmd = read_cli_cmd(cli_socket);
    printf("hola\n");
    if (cmd == NULL) {
        close(cli_socket);
        remove_client(cli_socket);
        fprintf(stderr, "Client disconnected\n");
        return (-84);
    }
    printf("Received command: \"%s\" from Client:%d\n", cmd, cli_socket);
    if (handle_cmd(cli_socket, cmd) == 84) {
        fprintf(stderr, "Error: can't handle command\n");
        return 84;
    }
    free(cmd);
    return 0;
}
