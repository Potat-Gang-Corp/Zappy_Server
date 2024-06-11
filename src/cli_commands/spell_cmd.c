/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** spell_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"

int cmd_broadcast(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    printf("Executing Broadcast command\n");
    return 0;
}

int cmd_fork(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    printf("Executing Fork command\n");
    return 0;
}

int cmd_incantation(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    printf("Executing Incantation command\n");
    return 0;
}
