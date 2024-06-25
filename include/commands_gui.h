/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** commands_gui
*/

#ifndef COMMANDS_GUI_H_
    #define COMMANDS_GUI_H_

/**
* @file commands_gui.h
* @brief Contains the commands of the gui
*/

/**
 * @brief Function to handle the gui commands
 * @param void
 *
 * @details will launch the process to execute the gui commands
 * @return nothing.
 */
void handle_gui_cmd(void);

/**
 * @brief Function to determien the content of a tile
 * @param items_t *item_start the start of the items list of the tile
 * @param int x the x position of the tile
 * @param int y the y position of the tile
 *
 * @details will etablish the content of the tile and send a message
 * to conclude the content.
 */
char *compute_tile_stock(items_t *item_start, int x, int y);

/**
 * @brief Function to process the tile and get the message
 * @param items_t *item_start the start of the items list of the tile
 * @param int *items_counter the counter of in items on a tile
 *
 * @details will check the content of the tile and return the inventory
 * of the tile requeted.
 * @return the counter of items on the tile.
 */
int *construct_message(items_t *item_start, int *items_counter);

/**
 * @brief Function to 
 */
int cmd_mct(char *command_type, int gui_socket);
char *build_message(char **bct_dict, map_t *map, int message_len);
char **build_bct_dict(map_t *map, int *message_len);
char *process_tile_and_get_message(map_t *map, int x, int y, int *message_len);
char *compute_tile_stock(items_t *item_start, int x, int y);

#endif /* !COMMANDS_GUI_H_ */
