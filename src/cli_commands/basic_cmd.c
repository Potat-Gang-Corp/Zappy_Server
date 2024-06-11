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
#include "../../include/commands.h"

int cmd_inventory(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    client_t *cli = get_client_by_socket(cli_socket);
    handle_inventory_command(cli);
    printf("Executing Inventory command\n");
    return 0;
}

int cmd_connect_nbr(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    client_t *cli = get_client_by_socket(cli_socket);
    handle_connect_nbr_command(cli);
    printf("Executing Connect_nbr command\n");
    return 0;
}
