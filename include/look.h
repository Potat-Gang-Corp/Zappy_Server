/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** look
*/

#ifndef LOOK_H_
    #define LOOK_H_

/**
* @file look.h
* @brief File for the look command
*/

/**
 * @brief level zero of the look command
 * @param msg Message to be sent
 * @param msg_size Size of the message
 * @param pos Position of the player
 * @return int Success or error
 */
int lvl_zero(char **msg, size_t *msg_size, position_t pos);

/**
 * @brief every level of the look command
 * @param msg Message to be sent
 * @param map Map structure
 * @param pos Position of the player
 * @param lvl Level of the look command
 * @return int Success or error
 */
int cmd_lvl(char **msg, map_t *map, position_t pos, int lvl);

#endif /* !LOOK_H_ */
