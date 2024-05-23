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

/**
 * @struct waiting_client_t
 * @brief define a linked list that puts users in the waiting list. To define a node 
 * we have to register the client socket and the name of the team of the player. 
 */
typedef struct waiting_client_s {
    int socket;
    char *team;
    TAILQ_ENTRY(waiting_client_s) entries;
} waiting_client_t;

/**
* @struct command_t
* @brief define a linked list that puts in a node each command sent by every user.
*/
typedef struct command_s {
    int cli_id;
    char *command;
    TAILQ_ENTRY(command_s) entries;
} command_t;

/**
* @struct server_t
* @brief struct that holds the server parameters
*/

typedef struct server_s {
    int maxfd;
    int socket;
    client_t *clients;
    TAILQ_HEAD(, waiting_client_s) waiting_list;
    TAILQ_HEAD(, command_s) commands;
    int port;
    struct sockaddr_in server;
    fd_set readfs;
    fd_set writefds;
    int nb_players;
} server_t;

#endif /* !STRUCT_SERVER_H_ */
