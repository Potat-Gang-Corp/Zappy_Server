/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** lower_cli_cd
*/

#include "server.h"
#include "get_instance.h"

int lower_cli_cd(client_t *cli)
{
    printf("cli->cd = %d\n", cli->cd);
    if (cli->cd > 0)
        cli->cd--;
    return 0;
}
