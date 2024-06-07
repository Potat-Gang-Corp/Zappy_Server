/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** move_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

int cmd_left(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    printf("Executing Left command\n");
    return 0;
}

int cmd_right(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    printf("Executing Right command\n");
    return 0;
}

int cmd_forward(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    printf("Executing Forward command\n");
    return 0;
}
