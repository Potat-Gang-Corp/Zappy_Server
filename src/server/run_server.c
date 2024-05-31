/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** run_server
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/my.h"

void handle_sigint(int sig)
{
    server_t *server = get_instance();

    (void)sig;
    if (server == NULL)
        return;
    close(server->socket);
    exit(0);
}

int run_server(void)
{
    server_t *server = get_instance();

    if (server == NULL)
        return 84;
    printf("server launched on port %d\n", server->port);
    signal(SIGINT, handle_sigint);

    while (1) {
        select_loop();
        if (FD_ISSET(server->socket, &server->readfs)) {
            accept_new_client();
        }
        handle_clients();
    }
    return 0;
}
