/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

/**
* @file server.h
* @brief Contains definitions of the server management functions
*/

//init_server.c

/**
 * @brief Function that init the server struct parameters
 * @param void no parameters are required.
 *
 * @details will set the components of the server structure to their default values, init 
 * the different linked list and will call the init_server_bis function to init the server.
 * @return return 0 if everything's good or 84 if an error occured.
 */

int init_server(void);

/**
 * @brief Function that init the construction process of the server
 * @param void no parameters are required.
 *
 * @details will call all of the necessary functions to create and launch
 * the server.
 * @return return 0 if everything's good or 84 if an error occured.
 */
static int init_server_bis(void);

/**
 * @brief Function that init the socket of the server
 * @param void no parameters are required.
 *
 * @details will create the socket of the server.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int init_socket(void);

/**
 * @brief Function that init the parameters of the server
 * @param void no parameters are required.
 *
 * @details will set the address of the server and the port.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int init_struct_addr(void);

/**
 * @brief Function that init the launch of the server
 * @param void no parameters are required.
 *
 * @details will bind the server to the address and port, set the socket to non blocking
 * and will call the init_server_listen function to listen to the server.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int init_server_launch(void);

/**
 * @brief Function that init the listening of the server
 * @param void no parameters are required.
 *
 * @details will listen to the server.
 * @return return 0 if everything's good or 84 if an error occured.
 */
static int init_server_listen(void);

//run_server.c

/**
 * @brief Function that run the server
 * @param void no parameters are required.
 *
 * @details will run the server main loop to accept new clients and handle them.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int run_server(void);

/**
 * @brief Function that handle the signal SIGINT
 * @param int sig the signal to handle.
 *
 * @details will close the server socket and exit the server if ctrl + c is detected.
 * @return void.
 */
void handle_sigint(int sig);

//accept_cli.c

/**
 * @brief Function that accept a new client connection
 * @param void no parameters are required.
 *
 * @details will check if the client socket is ready and accept the new client connection.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int accept_new_client(void);

/**
 * @brief Function that init the linked list of the server
 * @param int new_socket the socket of the new client.
 *
 * @details will check the team of the client.
 * @return return 0 if everything's good or 84 if an error occured.
 */
static int com_with_cli(int new_socket);

/**
 * @brief Function that check if the client is following the right team
 * @param char *team_name the name of the team.
 * @param int new_socket the socket of the new client.
 *
 * @details will check if the client is following the right team and 
 * share to the client the game parameters.
 * @return return 0 if everything's good or 84 if an error occured.
 */
static int following(char *team_name, int new_socket);

/**
 * @brief Function that check if the session is full
 * @param int new_socket the socket of the new client.
 * @param int nb_joueur the number of players.
 * @param int index the index of the team.
 *
 * @details will check if the session is full and add the client to the waiting list
 * or accept the connection and join the game.
 * @return return 0 if everything's good or 84 if an error occured.
 */
static int accept_loop(int new_socket, int nb_joueur, int index);

/**
 * @brief Function that add the client to the waiting list
 * @param int new_socket the socket of the new client.
 * @param int index the index of the team.
 *
 * @details will add the client to the waiting list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
static int add_to_waiting_list(int new_socket, const char *team);

/**
 * @brief Function that add the client to the main linked list
 * @param int new_socket the socket of the new client.
 * @param int index the index of the team.
 *
 * @details will check if the linked list is empty and redirect to the best process to
 * add to linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
static int add_to_ll(int new_socket, int index);

/**
 * @brief Function that add the client to the linked list
 * @param int new_socket the socket of the new client.
 * @param int index the index of the team.
 *
 * @details will add the client to the linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
static int add_to_ll_bis(int new_socket, int index);

/**
 * @brief Function that init the linked list of the server
 * @param int new_socket the socket of the new client.
 * @param int index the index of the team.
 *
 * @details will init the linked list of the server and add the first element
 * in the linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
static int init_ll(int new_socket, int index);

//read_write_cmd.c
int handle_clients(void);
static int cond_of_loop(int cli_socket, int index);
static int handle_cmd(int cli_socket, char *cmd);
static int find_socket(int cli_socket, struct client_s *cli, char *cmd);
static int add_command_to_list(int cli_id, const char *cmd);
int process_cli_cmd(int cli_socket, int index);
char *read_cli_cmd(int cli_socket);

//select_cli.c
int select_loop(void);
static int select_function(void);

//non_blocking_conf.c
int set_nonblocking(int fd);

#endif /* !SERVER_H_ */
