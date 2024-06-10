/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handling_game_command
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

void handle_left_command(client_t *cli)
{
    if (cli->pos.orientation == NORTH) {
        cli->pos.orientation = WEST;
    }
    if (cli->pos.orientation == WEST) {
        cli->pos.orientation = SOUTH;
    }
    if (cli->pos.orientation == SOUTH) {
        cli->pos.orientation = EAST;
    }
    if (cli->pos.orientation == EAST) {
        cli->pos.orientation = NORTH;
    }
    dprintf(cli->socket, "ok\r\n");
}

void handle_right_command(client_t *cli)
{
    if (cli->pos.orientation == NORTH) {
        cli->pos.orientation = EAST;
    }
    if (cli->pos.orientation == EAST) {
        cli->pos.orientation = SOUTH;
    }
    if (cli->pos.orientation == SOUTH) {
        cli->pos.orientation = WEST;
    }
    if (cli->pos.orientation == WEST) {
        cli->pos.orientation = NORTH;
    }
    dprintf(cli->socket, "ok\n");
}

int comp_cmd(char *command_type, client_t *cli, char *command)
{
    command = command;
    if (strcmp(command_type, "Left") == 0) {
        handle_left_command(cli);
        return 0;
    }
    if (strcmp(command_type, "Look") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Broadcast") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Eject") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Take") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Set") == 0) {
        return 0;
    }
    return 1;
}

int comp_cmd_bis(char *command_type, client_t *cli, char *command)
{
    command = command;
    cli = cli;
    if (strcmp(command_type, "Forward") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Right") == 0) {
        handle_right_command(cli);
        return 0;
    }
    if (strcmp(command_type, "Fork") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Incantation") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Connect_nbr") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Inventory") == 0) {
        return 0;
    }
    return 1;
}

void execute_game_cmd(client_t *cli, char *command)
{
    char *buffer = strdup(command);
    char *command_type = strtok(buffer, " \r\n");
    int result = -1;

    result = comp_cmd_bis(command_type, cli, command);
    if (result == 1)
        comp_cmd(command_type, cli, command);
}
