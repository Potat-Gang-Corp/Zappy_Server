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

void handle_gui_cmd(void);
char *compute_tile_stock(items_t *item_start, int x, int y);
int *construct_message(items_t *item_start, int *items_counter);

#endif /* !COMMANDS_GUI_H_ */
