/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** lower_cli_cd
*/

#include "server.h"
#include "get_instance.h"

/**
 * @file lower_cli_cd.c
 * @brief File containing functions to lower client cd
*/
int lower_cli_cd(client_t *cli)
{
    if (cli->cd > 0)
        cli->cd--;
    return 0;
}
