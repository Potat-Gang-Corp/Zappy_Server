/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** lower_nb_cmd_cli
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

void lower_nb_cmd(client_t *cli)
{
    if (cli->nb_commands > 0)
        cli->nb_commands--;
}
