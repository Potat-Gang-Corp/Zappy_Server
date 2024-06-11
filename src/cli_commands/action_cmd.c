/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** action_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"

int cmd_look(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    printf("Executing Look command\n");
    return 0;
}

int cmd_eject(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    printf("Executing Eject command\n");
    return 0;
}

int cmd_take(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    client_t *cli = get_client_by_socket(cli_socket);
    handle_take_command(cli, command_type);
    printf("Executing Take command\n");
    return 0;
}

int cmd_set(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    client_t *cli = get_client_by_socket(cli_socket);
    handle_set_command(cli, command_type);
    printf("Executing Set command\n");
    return 0;
}
