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
    char *cmd = malloc(sizeof(char) * (1024 + 1));
    char *parse_command;
    char *result;
    int n = read(cli_socket, cmd, 1024);

    if (cmd == NULL)
        return NULL;
    if (n < 0 || n == 0) {
        free(cmd);
        return NULL;
    }
    cmd[n] = '\0';
    parse_command = strtok(cmd, "\r\n");
    printf("Reading command from Client %d: %s\n", cli_socket, parse_command);
    if (parse_command) {
        result = strdup(parse_command);
        free(cmd);
        return result;
    }
    free(cmd);
    return NULL;
}
