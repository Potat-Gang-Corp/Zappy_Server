/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** look
*/

#ifndef LOOK_H_
    #define LOOK_H_

int cmd_one(char **msg, map_t *map, position_t pos);

int cmd_two(char **msg, map_t *map, position_t pos);

int cmd_three(char **msg, map_t *map, position_t pos);

int cmd_four(char **msg, map_t *map, position_t pos);

int cmd_five(char **msg, map_t *map, position_t pos);

int cmd_six(char **msg, map_t *map, position_t pos);

int cmd_seven(char **msg, map_t *map, position_t pos);

int cmd_eight(char **msg, map_t *map, position_t pos);

typedef int (*lvl_func_t)(char **, map_t *, position_t);

typedef struct {
    int cmd_lvl;
    lvl_func_t command_func;
} table_level_t;

table_level_t table_level[] = {
    {1, cmd_one},
    {2, cmd_two},
    {3, cmd_three},
    {4, cmd_four},
    {5, cmd_five},
    {6, cmd_six},
    {7, cmd_seven},
    {8, cmd_eight},
};

#endif /* !LOOK_H_ */
