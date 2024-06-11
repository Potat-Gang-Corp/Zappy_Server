/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** commands_entry_gui
*/

#ifndef COMMANDS_ENTRY_GUI_H_
#define COMMANDS_ENTRY_GUI_H_

#include "my.h"

int cmd_msz(char *command_type, int gui_socket);

int cmd_bct(char *command_type, int gui_socket);

int cmd_mct(char *command_type, int gui_socket);

int cmd_tna(char *command_type, int gui_socket);

int cmd_ppo(char *command_type, int gui_socket);

int cmd_plv(char *command_type, int gui_socket);

int cmd_pin(char *command_type, int gui_socket);

int cmd_sgt(char *command_type, int gui_socket);

int cmd_sst(char *command_type, int gui_socket);

typedef int (*cmd_func_t)(char *, int);

typedef struct {
    char *command_name;
    cmd_func_t command_func;
} command_gui_t;

command_gui_t command_table[] = {
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
