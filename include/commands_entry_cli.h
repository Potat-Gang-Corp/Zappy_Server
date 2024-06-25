/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** commands_entry_t
*/

#ifndef COMMANDS_ENTRY_T_H_
    #define COMMANDS_ENTRY_T_H_

    #include "my.h"

/**
* @file commands_entry_cli.h
* @brief File for the client commands
*/

/**
 * @brief Function to handle the left command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will change the orientation of the client to the left
 * @return nothing.
 */
int cmd_left(char *command_type, int cli_socket);
/**
 * @brief Function to handle the right command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will change the orientation of the client to the right
 * @return nothing.
 */
int cmd_right(char *command_type, int cli_socket);

/**
 * @brief Function to handle the forward command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will move the client forward
 * @return nothing.
 */
int cmd_forward(char *command_type, int cli_socket);

/**
 * @brief Function to handle the look command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will move the client forward related to his orientation.
 * @return nothing.
 */
int cmd_look(char *command_type, int cli_socket);

/**
 * @brief Function to handle the incantation command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will start the incantation
 * @return nothing.
 */

int cmd_incantation(char *command_type, int cli_socket);

/**
 * @brief Function to handle the fork command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will fork the client
 * @return nothing.
 */

int cmd_fork(char *command_type, int cli_socket);

/**
 * @brief Function to handle the broadcast command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will broadcast a message to all the clients
 * @return nothing.
 */

int cmd_broadcast(char *command_type, int cli_socket);

/**
 * @brief Function to handle the eject command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will eject the clients on the same tile
 * @return nothing.
 */

int cmd_eject(char *command_type, int cli_socket);

/**
 * @brief Function to handle the take command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will take an item on the map and put it
 * in the client inventory
 * @return nothing.
 */

int cmd_take(char *command_type, int cli_socket);

/**
 * @brief Function to handle the set command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will take an item from the client inventory and put it
 * on the tile of the client.
 * @return nothing.
 */

int cmd_set(char *command_type, int cli_socket);

/**
 * @brief Function to handle the inventory command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will return the inventory of the client
 * @return nothing.
 */

int cmd_inventory(char *command_type, int cli_socket);

/**
 * @brief Function to handle the connect_nbr command
 * @param command_type the command type
 * @param cli_socket the client socket
 *
 * @details will return the number of clients that can be connected
 * @return nothing.
 */

int cmd_connect_nbr(char *command_type, int cli_socket);

typedef int (*cmd_func_t)(char *, int);

/**
 * @struct command_entry_t
 * @brief contains the command name as well as the function ptr associated
 */
typedef struct {
    char *command_name;
    cmd_func_t command_func;
} command_entry_t;

command_entry_t command_table_cli[] = {
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

#endif /* !COMMANDS_ENTRY_T_H_ */
