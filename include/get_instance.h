/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** get_instance
*/

#ifndef GET_INSTANCE_H_
    #define GET_INSTANCE_H_

    #include "my.h"
    #include "struct_server.h"
    #include "struct_map.h"
    #include "struct_client.h"
    #include "struct_game.h"

/**
* @file get_instance.h
* @brief get the server, map and game instances prototypes
*/
/**
 * @brief Function that return the server instance.
 * @param void
 *
 * @details will return an instance of the server(singleton).
 * @return server_t * return the server instance.
 */
server_t *get_instance(void);
/**
 * @brief Function that return the map instance.
 * @param void
 *
 * @details will return an instance of the map(singleton).
 * @return map_t * return the map instance.
 */
map_t *get_map_instance(void);
/**
 * @brief Function that return the game instance.
 * @param void
 *
 * @details will return an instance of the game(singleton).
 * @return game_t * return the game instance.
 */
game_t *get_game_instance(void);

/**
 * @brief Function that return the client by it socket.
 * @param int cli_socket the client socket
 *
 * @details will return the structure of the client by it socket.
 * @return client_t * return the client instance.
 */
client_t *get_client_by_socket(int cli_socket);

#endif /* !GET_INSTANCE_H_ */
