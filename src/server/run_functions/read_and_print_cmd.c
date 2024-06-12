/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** read_write_cmd
*/

#include "../../../include/struct_server.h"
#include "../../../include/get_instance.h"
#include "../../../include/my.h"
#include "../../../include/server.h"

/**
* @file read_and_print_cmd.c
* @brief read and write command for the server
*/
char *parse_command(char *cmd)
{
    char *parse_command = strtok(cmd, "\r\n");

    if (parse_command)
        return strdup(parse_command);
    return NULL;
}

char *read_from_socket(int cli_socket, int *bytes_read)
{
    char *buffer = malloc(sizeof(char) * (1024 + 1));

    if (buffer == NULL) {
        perror("malloc");
        return NULL;
    }
    *bytes_read = read(cli_socket, buffer, 1024);
    if (*bytes_read <= 0) {
        free(buffer);
        return NULL;
    }
    buffer[*bytes_read] = '\0';
    return buffer;
}

char *read_cli_cmd(int cli_socket)
{
    int bytes_read;
    char *cmd = read_from_socket(cli_socket, &bytes_read);
    char *result = NULL;

    if (cmd == NULL) {
        fprintf(stderr, "Error reading command from Client %d\n", cli_socket);
        return NULL;
    }
    printf("Reading command from Client %d: %s", cli_socket, cmd);
    result = parse_command(cmd);
    free(cmd);
    return result;
}
