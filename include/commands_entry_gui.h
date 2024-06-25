/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** commands_entry_gui
*/

#ifndef COMMANDS_ENTRY_GUI_H_
    #define COMMANDS_ENTRY_GUI_H_

    #include "my.h"

/**
 * @brief Function to handle the msz command
 * @param command_type the command type
 * @param gui_socket the gui socket
 *
 * @details will send to the gui the map size
 * @return nothing special.
 */
int cmd_msz(char *command_type, int gui_socket);

/**
 * @brief Function to handle the bct command
 * @param command_type the command type
 * @param gui_socket the gui socket
 *
 * @details will send to the gui the content of a tile
 * @return nothing special.
 */

int cmd_bct(char *command_type, int gui_socket);

/**
 * @brief Function to handle the mct command
 * @param command_type the command type
 * @param gui_socket the gui socket
 *
 * @details will send to the gui the content of all the tiles
 * @return nothing special.
 */
int cmd_mct(char *command_type, int gui_socket);

/**
 * @brief Function to handle the tna command
 * @param command_type the command type
 * @param gui_socket the gui socket
 *
 * @details will send to the gui the name of all the teams
 * @return nothing special.
 */

int cmd_tna(char *command_type, int gui_socket);

/**
 * @brief Function to handle the ppo command
 * @param command_type the command type
 * @param gui_socket the gui socket
 *
 * @details will send to the gui the position and orientation of a player
 * @return nothing special.
 */

int cmd_ppo(char *command_type, int gui_socket);

/**
 * @brief Function to handle the plv command
 * @param command_type the command type
 * @param gui_socket the gui socket
 *
 * @details will send to the gui the level of a player
 * @return nothing special.
 */

int cmd_plv(char *command_type, int gui_socket);

/**
 * @brief Function to handle the pin command
 * @param command_type the command type
 * @param gui_socket the gui socket
 *
 * @details will send to the gui the inventory of a player
 * @return nothing special.
 */

int cmd_pin(char *command_type, int gui_socket);

/**
 * @brief Function to handle the sgt command
 * @param command_type the command type
 * @param gui_socket the gui socket
 *
 * @details will send to the gui the time unit
 * @return nothing special.
 */

int cmd_sgt(char *command_type, int gui_socket);

/**
 * @brief Function to handle the sst command
 * @param command_type the command type
 * @param gui_socket the gui socket
 *
 * @details will set a new time unit
 * @return nothing special.
 */

int cmd_sst(char *command_type, int gui_socket);

typedef int (*cmd_func_t)(char *, int);

typedef struct {
    char *command_name;
    cmd_func_t command_func;
} command_gui_t;

command_gui_t command_table_gui[] = {
    {"msz", cmd_msz},
    {"bct", cmd_bct},
    {"mct", cmd_mct},
    {"tna", cmd_tna},
    {"ppo", cmd_ppo},
    {"plv", cmd_plv},
    {"pin", cmd_pin},
    {"sgt", cmd_sgt},
    {"sst", cmd_sst},
    {NULL, NULL}
};

#endif /* !COMMANDS_ENTRY_GUI_H_ */
