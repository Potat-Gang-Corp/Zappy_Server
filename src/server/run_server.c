/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** run_server
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "server.h"

void handle_sigint(int sig)
{
    server_t *server = get_instance();

    (void)sig;
    //gérer le cas du ctrl + C
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
    signal(SIGINT, handle_sigint); //permet de gérer le ctrl + C
    while(1) {
        select_loop(); //permet de gérer les sockets mais jusqu'à quel point pour notre serv
        accept_new_client(); //dépends au début du nbr max de cli par team 
        //puis ensuite oeuf + gestion waiting list
        handle_clients(); //ça endroit ou on va récup cmd à rajouter dans le FIFO
    }
    return 0;
}
