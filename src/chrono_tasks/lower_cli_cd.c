/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** lower_cli_cd
*/

#include "server.h"
#include "get_instance.h"

int lower_cli_cd(void)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->cd > 0)
            cli->cd--;
    }
    return 0;
}
