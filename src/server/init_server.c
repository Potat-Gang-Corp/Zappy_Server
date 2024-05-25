/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** init_server
*/

#include "struct_server.h"
#include "get_instance.h"
#include "my.h"

int init_server_launch(void) //tjr bind et listen ? 
{
    server_t *server = get_instance();

    if (bind(server->socket, (struct sockaddr *)&server->sockaddr,
        sizeof(server->sockaddr)) < 0) {
        perror("bind");
        return 84;
    }
    if (listen(server->socket, 3) < 0) {
        perror("listen");
        return 84;
    }
    return 0;
}

int init_struct_addr(void) //same params ?
{
    server_t *server = get_instance();

    server->sockaddr.sin_family = AF_INET;
    server->sockaddr.sin_addr.s_addr = INADDR_ANY;
    server->sockaddr.sin_port = htons(server->port);
    return 0;
}

int init_socket(void) //same flag dans socket ?
{
    server_t *server = get_instance();

    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1) {
        perror("socket");
        return 84;
    }
    return 0;
}

static int init_server_bis(void)
{
    if (init_socket() == 84) {
        fprintf(stderr, "Error: socket creation failed\n");
        return 84;
    }
    if (init_struct_addr() == 84) {
        fprintf(stderr, "Error: struct addr failed\n");
        return 84;
    }
    if (init_server_launch() == 84) {
        fprintf(stderr, "Error: server launch failed\n");
        return 84;
    }
    return 0;
}

int init_server(void)
{
    server_t *server = get_instance();

    if (server == NULL) {
        fprintf(stderr, "Error: server non existant\n");
        return 84;
    }
    server->maxfd = 0;
    server->nb_players = 0;
    server->clients = NULL; //gestion clients à un autre endroit ? 
    TAILQ_INIT(&server->waiting_list); //bien regarder ce que c'est
    TAILQ_INIT(&server->commands); //bien regarder ce que c'est
    if (init_server_bis() == 84) {
        fprintf(stderr, "Error: server init failed\n");
        return 84;
    }
    return 0;
}
