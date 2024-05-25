/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** accept_cli
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"

static int accept_loop(int new_socket)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    new_socket = 0;
    for (cli = server->clients; cli; cli = cli->next) { //on parcourt les clients
        if (cli->socket == 0) { //on cherche un client qui n'est pas connecté et rajouter condition oeuf ?
            cli->socket = new_socket;
            printf("New client connected, socket fd is %d\n", new_socket);
            //printf Welcome ; team ; nbr_max ;
            break;
        }
    }
    return 0;
}

int accept_new_client(void)
{
    server_t *server = get_instance();
    int new_socket = 0;

    if (FD_ISSET(server->socket, &server->readfs)) { //si le socket est dans le readfs
        new_socket = accept(server->socket, NULL, NULL); //accepte la connexion A REVOIR du coup
        if (new_socket < 0) {
            perror("accept");
            return 84;
        }
        accept_loop(new_socket);
    }
}
