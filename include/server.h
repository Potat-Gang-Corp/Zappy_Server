/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "struct_client.h"
    #include "struct_game.h"
    #include "struct_server.h"

/**
* @file server.h
* @brief Contains definitions of the server management functions
*/

//init_server.c

/**
 * @brief Function that init the server struct parameters
 * @param void no parameters are required.
 *
 * @details will set the components of the server structure
 * to their default values, init
 * the different linked list and will call the init_server_bis
 * function to init the server.
 * @return return 0 if everything's good or 84 if an error occured.
 */

int init_server(void);

/**
 * @brief Function that init the construction process of the server
 * @param void no parameters are required.
 *
 * @details will call all of the necessary functions to create and launch
 * the server. Such as fill the sockeaddr structure
 * @return return 0 if everything's good or 84 if an error occured.
 */
int init_server_bis(void);

/**
 * @brief Function that init the socket of the server
 * @param void no parameters are required.
 *
 * @details will create the socket of the server.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int init_socket(void);

/**
 * @brief Function that init the launch of the server
 * @param void no parameters are required.
 *
 * @details will bind the server to the address and port,
 * set the socket to non blocking
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
int init_server_listen(void);

//run_server.c

/**
 * @brief Function that run the server
 * @param void no parameters are required.
 *
 * @details will run the server main loop to
 * accept new clients and handle them.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int run_server(void);

/**
 * @brief Function that handle the signal SIGINT
 * @param int sig the signal to handle.
 *
 * @details will close the server socket and
 * exit the server if ctrl + c is detected.
 * @return void.
 */
void handle_sigint(int sig);

//accept_cli.c

/**
 * @brief Function that accept a new client connection
 * @param void no parameters are required.
 *
 * @details will check if the client socket is
 * ready and accept the new client connection.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int accept_new_client(void);

/**
 * @brief Function that define the client parameters
 * @param client_t *new_client the new client.
 * @param int client_socket the socket of the client.
 *
 * @details will define the client parameters.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int add_client(int client_socket);

/**
 * @brief Function that define the client parameters
 * @param client_t *new_client the new client.
 * @param int client_socket the socket of the client.
 *
 * @details will define the client parameters and insert
 * the client in the linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
void define_client_parameters(client_t *new_client, int client_socket);

/**
 * @brief Function that check if the session is full
 * @param int new_socket the socket of the new client.
 * @param int nb_joueur the number of players.
 * @param int index the index of the team.
 *
 * @details will check if the session is full
 * and add the client to the waiting list
 * or accept the connection and join the game.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int accept_loop(int new_socket, int nb_joueur, int index);

//accept_ll.c
/**
 * @brief Function that handles the error case of the initialisation of the ll
 * @param int new_socket the socket of the new client.
 *
 * @details will return 84 if the server's instance or the game is instance is
 *  non existant.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int init_ll_error_handling(int new_socket);

/**
 * @brief Function that init the linked list of the server
 * @param int new_socket the socket of the new client.
 * @param int index the index of the team.
 *
 * @details will init the linked list of the server and add the first element
 * in the linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int init_ll(int new_socket, int index);

/**
 * @brief Function that add the client to the linked list
 * @param int new_socket the socket of the new client.
 * @param int index the index of the team.
 *
 * @details will add the client to the linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int add_to_ll_bis(int new_socket, int index);

/**
 * @brief Function that add the client to the main linked list
 * @param int new_socket the socket of the new client.
 * @param int index the index of the team.
 *
 * @details will check if the linked list is empty
 * and redirect to the best process to
 * add to linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int add_to_ll(int new_socket, int index);

/**
 * @brief Function that add the client to the waiting list
 * @param int new_socket the socket of the new client.
 * @param int index the index of the team.
 *
 * @details will add the client to the waiting list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int add_to_waiting_list(int new_socket, const char *team);

//read_write_cmd.c

/**
 * @brief Function that handle the clients
 * @param void no parameters are required.
 *
 * @details will handle the clients and their commands
 * to add them in the linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int handle_clients(void);

/**
 * @brief Function that add the client command to the related linked list
 * @param int cli_socket the socket of the client.
 *
 * @details will add the client command to the related linked list.
 * @return return the command of the client.
 */
int add_command_to_list(int cli_id, const char *cmd, double execution_time);

/**
 * @brief Function that delete the client from the linked list
 * @param client_t **prev the previous client entity.
 * @param client_t **cli the client entity that contains client informations.
 * @param client_t **head the head of the linked list.
 *
 * @details will delete the client from the linked list.
 * @return return nothing.
 */
void handle_client_disconnection(client_t **prev,
    client_t **cli, client_t **head);

/**
 * @brief Function that detect command of the
 * client and add it to the linked list
 * @param client_t *cli the client entity that contains client informations.
 * @param client_t **prev the previous client entity.
 * @param server_t *server the server entity that contains server informations.
 *
 * @details will check the command sent by the client, it's time of execution
 * and add it to the linked list.
 * @return return nothing.
 */
void read_buffer_to_list(client_t *cli);

/**
 * @brief Function that detect the max command capacity of the client
 * @param int cli_id the client id.
 *
 * @details will check if the client has reached the maximum command capacity
 * and if not increment the number of commands to authorize a new one.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int detect_max_command_capacity(int cli_id);

//select.c

/**
 * @brief Function that prepare the select protocol
 * @param void no parameters are required.
 *
 * @details will clear and set the environment to receive commands.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int select_loop(void);

/**
 * @brief Function that launch the select protocol
 * @param void no parameters are required.
 *
 * @details will launch the select protocol.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int select_function(void);

//handling_login_phase.c

/**
 * @brief Function to handle the client login phase
 * @param client_t *cli represent the client entity
 * that contains client informations.
 * @param char *command represent the team name sent by the client.
 *
 * @details will check if the team name is valid
 * and if the team is full or not.
 * @return return noting.
 */
void handle_cli_login(client_t *cli, char *command);

/**
 * @brief Function to check if the team name is valid or not
 * @param char *team_name represent the team name sent by the client.
 * @param client_t *cli represent the client entity
 * that contains client informations.
 *
 * @details will check if the team name exists or
 * not and so change connected status of the client.
 * @return return 0 if there is no error, and 84 if there is an error.
 */
int detect_team_validity(char *team_name, client_t *cli);

/**
 * @brief Function to handle the team full status
 * @param client_t *cli represent the client entity
 * that contains client informations.
 * @param team_t *team represent the team
 * entity that contains team informations.
 * @param game_t *game represent the game
 * entity that contains game informations.
 * @param char *team_name represent the team name sent by the client.
 *
 * @details will check if the team is full
 * or not and so change the team status.
 * It Will put the client in the waiting list if the team is full.
 * @return return 0 always.
 */
int handle_team_full_status(client_t *cli, team_t *team, game_t *game,
    char *team_name);

//handling_game_phase.c

/**
 * @brief Function to execute the game commands
 * @param int cli_socket represent the client socket.
 * @param char *command represent the command sent by the client.
 *
 * @details will execute the game commands.
 * @return return noting.
 */
void execute_game_cmd(int cli_socket, char *command);

/**
 * @brief Function to compare the command type
 * @param char *command_type represent the command type sent by the client.
 *
 * @details will compare the command type.
 * @return return 0 if the command type match,
 * and 1 if the command type doesn't match.
 */
int comp_cmd(char *command_type);

/**
 * @brief Function to compare the command type
 * @param char *command_type represent the command type sent by the client.
 *
 * @details will compare the command type.
 * @return return 0 if the command type match,
 * and 1 if the command type doesn't match.
 */
int comp_cmd_bis(char *command_type);

//send_cli_answers.c

/**
 * @brief Function to load the profile and execute the command
 * @param void no parameters are required.
 *
 * @details will load and execute all of the commands
 * received by all of the client.
 * @return return noting.
 */
void execute_cli_cmd(void);

/**
 * @brief Function to detect if the client is waiting
 * @param int cli_socket represent the client socket.
 *
 * @details will detect if the client who sent the command is waiting or not.
 * @return return noting.
 */
int detect_client_waiting(int client_socket);

/**
 * @brief Function to load the profile and execute the command
 * @param int cli_socket represent the client socket.
 * @param char *command represent the command sent by the client.
 *
 * @details will find the profile link to the client socket and
 * will redirect the client to the right process if the client
 * is connected or not.
 * @return return noting.
 */
void load_profile_and_exec(int cli_socket, char *command);

/**
 * @brief Function to execute the client commands
 * @param double current_time represent the current time in milliseconds.
 * @param command_t *cmd represent the command
 * entity that contains command informations.
 *
 * @details will call the main to execute the
 * command sent if there is the time and
 * after delete the command from the linked list.
 * @return return noting.
 */
void execute_cli_cmd_bis(double start, command_t *cmd);

//timer.c

/**
 * @brief Function to compute the execution time of a command
 * @param char *command represent the command sent by the client.
 *
 * @details will detect if the command sent by the client
 * require a specific execution time and compute it or if
 * not return the default value.
 * @return return the execution time of the command.
 */
double detect_execution_time(char *command);

/**
 * @brief Function to get the current time in milliseconds
 * @param void no parameters are required.
 *
 * @details will get the current time in milliseconds.
 * @return return the current time in milliseconds.
 */
double current_time_millis(void);

//op_cli_ll.c

/**
 * @brief Function to remove a client from the linked list
 * @param int cli_socket represent the client socket.
 *
 * @details will remove the client from the linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int remove_client(int cli_socket);

//read_and_print_cmd.c

/**
 * @brief Function to read the client command
 * @param int cli_socket represent the client socket.
 *
 * @details will read the client command.
 * @return return the command of the client.
 */
char *read_cli_cmd(int cli_socket);

/**
 * @brief Function to clean the game structure
 * @param void no parameters are required.
 *
 * @details will deallocate the game structure.
 * @return return nothing.
 */
void clean_game_struct(void);

/**
 * @brief Function to clean the team structure
 * @param void no parameters are required.
 *
 * @details will deallocate the team structure
 * by iterating on each element of the structure.
 * @return return nothing.
 */
void clean_team_struct(void);

/**
 * @brief Function to clean the map structure
 * @param void no parameters are required.
 *
 * @details will deallocate each element of
 * the map structure.
 * @return return nothing.
 */
void clean_map_struct(void);

/**
 * @brief Function to clean the tiles structure
 * @param void no parameters are required.
 *
 * @details will deallocate each element of
 * the tiles structure by iterating on
 * each of them.
 * @return return nothing.
 */
void clean_tiles_struct(void);

/**
 * @brief Function to verify the existence
 * of the tile element
 * @param tile_t *tile represent a portion of map
 *
 * @details will verify that the tile element
 * is not empty
 * @return nothing.
 */
void checking_existence_tile_element(tile_t *tile);

/**
 * @brief Function to clean the item linked list
 * @param items_t *items represent the items linked list
 *
 * @details will deallocate each element of
 * the items linked list.
 * @return nothing.
 */
void clean_item_linked_list(items_t **items);

/**
 * @brief Function to clean the client structure
 * @param void no parameters are required.
 *
 * @details will deallocate each element of
 * the client structure.
 * @return nothing.
 */
void clean_client_struct(void);

/**
 * @brief Function to clean the server data
 * @param void no parameters are required.
 *
 * @details will deallocate the server structure.
 * @return nothing.
 */
void clean_server_data(void);

/**
 * @brief Function to clean the commands list
 * @param server_t *server represent the server structure
 *
 * @details will deallocate each element of
 * the commands list.
 * @return nothing.
 */
void clean_commands_queue(server_t *server);

/**
 * @brief Function to clean the waiting list
 * @param server_t *server represent the server structure
 *
 * @details will deallocate each element of
 * the waiting list.
 * @return nothing.
 */
void clean_waiting_list(server_t *server);


/**
 * @brief Function to find the client and the previous client
 * @param int cli_socket represent the client socket.
 * @param client_t **prev_out represent the previous client.
 *
 * @details will find the client and the previous client.
 * @return return the client.
 */
client_t *find_client_and_prev(int cli_socket, client_t **prev_out);

/**
 * @brief Parses the initial line of a command.
 * @param char *cmd A pointer to the command string to be parsed.
 *
 * @details This function parses the command string
 * to extract the command without newline characters
 * and returns a pointer to the newly allocated.
 * @return char* Returns a pointer to the newly
 * allocated string containing the parsed command
 * or NULL if no command is found.
 */
char *parse_command(char *cmd);

/**
 * @brief Function to detect the maximum command capacity of the client
 * @param int cli_socket represent the client socket.
 * @param client_t **prev_out represent the previous client.
 *
 * @details will detect if a client has sent too many commands and
 * if it's ok increment the number of commands of the client.
 * @return return 0 if it's ok, or 84 if an error occured.
 */
int max_cmd_cli(int cli_id);

/**
 * @brief Function to add a command to the linked list
 * @param int cli_id represent the client id.
 * @param const char *cmd represent the command sent by the client.
 * @param double execution_time represent the execution time of the command.
 *
 * @details will add the command to the linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int add_cmd_to_ll(int cli_id, const char *cmd, double execution_time);

/**
 * @brief Function to add a client to the linked list
 * @param client_t *new_client represent the new client.
 * @param int client_socket represent the client socket.
 *
 * @details will add the client to the linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
void add_cli_to_ll(client_t *new_client, int client_socket);

/**
 * @brief Function to handle the team full status
 * @param client_t *cli represent the client entity
 * that contains client informations.
 * @param team_t *team represent the team entity
 * that contains team informations.
 * @param char *team_name represent the team name sent by the client.
 *
 * @details will check if the team is full
 * or not and so change the status for the client.
 * @return return 0 always.
 */
int handle_team_full(client_t *cli, team_t *team, char *team_name);

/**
 * @brief Function to remove the found client
 * @param client_t *prev represent the previous client.
 * @param client_t *cli represent the client entity
 * that contains client informations.
 *
 * @details will remove the found client from the linked list.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int remove_found_client(client_t *prev, client_t *cli);

/**
 * @brief Function to find the client and the previous client
 * @param int cli_socket represent the client socket.
 * @param client_t **prev_out represent the previous client.
 *
 * @details will find the client and the previous client.
 * @return return the client.
 */
client_t *find_client_and_prev(int cli_socket, client_t **prev_out);


char *read_from_socket(int cli_socket, int *bytes_read);

/**
 * @brief Function to insert a new client
 * @param client_t *cli represent the client entity
 * that contains client informations.
 * @param server_t *server represent the server entity
 * that contains server informations.
 *
 * @details This function checks if the socket descriptor
 * of the new client is greater than the current
 * maximum file descriptor stored in the server structure.
 * If it is, it updates the maximum file descriptor.
 */
void insert_new_client(client_t *cli, server_t *server);

/**
 * @brief Function to load the command line
 * interface and execute the command
 * @param int cli_socket represent the client
 * socket.
 * @param char *command represent the command
 * sent by the client.
 *
 * @details will load the command line interface
 * and redirect to the good process to execute command.
 * @return nothing.
 */
void load_cli_and_exec(int cli_socket, char *command);


#endif /* !SERVER_H_ */
