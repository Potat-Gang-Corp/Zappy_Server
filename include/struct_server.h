/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** struct_server.h
*/

#ifndef STRUCT_SERVER_H_
    #define STRUCT_SERVER_H_

    #include "my.h"
/**
 * @file struct_server.h
 * @brief defines the data structures used in the project for the
 * server, such as client, team, etc.
 */

typedef struct team_s {
    char *name;
    int max_clients;
    struct team_s *next;
} team_t;

typedef struct server_s {
    int maxfd;
    int socket;
    struct client_s *clients;
    struct team_s *teams;
    queue_t *waiting_list;
    queue_t *commands;
    int port;
    struct sockaddr_in server;
    fd_set readfs;
    fd_set writefds;
} server_t;

server_t *get_instance(void);
#endif /* !STRUCT_SERVER_H_ */