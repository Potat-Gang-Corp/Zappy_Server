/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** struct_server.h
*/

#ifndef STRUCT_SERVER_H_
    #define STRUCT_SERVER_H_

    #include "my.h"
    #include "struct_client.h"
/**
 * @file struct_server.h
 * @brief defines the data structures used in the project for the
 * server, such as client, team, etc.
 */

typedef struct waiting_client_s {
    int socket;
    char *team;
    TAILQ_ENTRY(waiting_client_s) entries;
} waiting_client_t;

typedef struct team_s {
    char *name;
    int max_clients;
    int cpt_egg;
} team_t;

typedef struct command_s {
    int cli_id;
    char *command;
    TAILQ_ENTRY(command_s) entries;
} command_t;

typedef struct server_s {
    int maxfd;
    int socket;
    client_t *clients;
    team_t **teams;
    TAILQ_HEAD(, waiting_client_s) waiting_list;
    TAILQ_HEAD(, command_s) commands;
    int port;
    struct sockaddr_in server;
    fd_set readfs;
    fd_set writefds;
} server_t;

server_t *get_instance(void);
#endif /* !STRUCT_SERVER_H_ */
