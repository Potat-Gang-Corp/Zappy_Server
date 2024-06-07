/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** commands
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "my.h"

int cmd_left(char *command_type, int cli_socket);

int cmd_right(char *command_type, int cli_socket);

int cmd_forward(char *command_type, int cli_socket);

int cmd_look(char *command_type, int cli_socket);

int cmd_incantation(char *command_type, int cli_socket);

int cmd_fork(char *command_type, int cli_socket);

int cmd_broadcast(char *command_type, int cli_socket);

int cmd_eject(char *command_type, int cli_socket);

int cmd_take(char *command_type, int cli_socket);

int cmd_set(char *command_type, int cli_socket);

int cmd_inventory(char *command_type, int cli_socket);

int cmd_connect_nbr(char *command_type, int cli_socket);

typedef int (*cmd_func_t)(char *, int);

typedef struct {
    char *command_name;
    cmd_func_t command_func;
} command_entry_t;

command_entry_t command_table[] = {
    {"Left", cmd_left},
    {"Look", cmd_look},
    {"Broadcast", cmd_broadcast},
    {"Connect_nbr", cmd_connect_nbr},
    {"Eject", cmd_eject},
    {"Forward", cmd_forward},
    {"Fork", cmd_fork},
    {"Incantation", cmd_incantation},
    {"Inventory", cmd_inventory},
    {"Right", cmd_right},
    {"Set", cmd_set},
    {"Take", cmd_take},
    {NULL, NULL}
};

#endif /* !COMMANDS_H_ */
