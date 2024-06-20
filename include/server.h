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

typedef struct timespec timespec_t;
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
int add_cmd_to_ll(int cli_id, const char *cmd);

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
int detect_max_cmd_capacity(int cli_id);

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
 * not and so change connected logged of the client.
 * @return return 0 if there is no error, and 84 if there is an error.
 */
int detect_team_validity(char *team_name, client_t *cli);

//handling_game_phase.c

/**
 * @brief Function to execute the game commands
 * @param client_t *cli represent the client entity
 * @param char *command represent the command sent by the client.
 *
 * @details will execute the game commands.
 * @return return noting.
 */
void execute_game_cmd(int index_cli, char *command);

/**
 * @brief Function to compare the command type
 * @param char *command_type represent the command type sent by the client.
 * @param client_t *cli represent the client entity
 * @param char *command represent the command sent by the client.
 *
 * @details will compare the command type.
 * @return return 0 if the command type match,
 * and 1 if the command type doesn't match.
 */
int comp_cmd(char *command_type, client_t *cli, char *command);

/**
 * @brief Function to compare the command type
 * @param char *command_type represent the command type sent by the client.
 * @param client_t *cli represent the client entity
 * @param char *command represent the command sent by the client.
 *
 * @details will compare the command type.
 * @return return 0 if the command type match,
 * and 1 if the command type doesn't match.
 */
int comp_cmd_bis(char *command_type, client_t *cli, char *command);

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
int execute_cli_cmd_bis(command_t *cmd);

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
int add_cmd_to_ll(int cli_id, const char *cmd);

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
 * @brief Function to handle the team full logged
 * @param client_t *cli represent the client entity
 * that contains client informations.
 * @param team_t *team represent the team entity
 * that contains team informations.
 * @param char *team_name represent the team name sent by the client.
 *
 * @details will check if the team is full
 * or not and so change the logged for the client.
 * @return return 0 always.
 */
int handle_team_full(client_t *cli, int team_index, char *team_name);

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

/**
 * @brief Function to read the command sent by the client
 * @param int cli_socket represent the client socket.
 * @param int *bytes_read represent the number of bytes read.
 * @return char* Returns a pointer to the newly
*/
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
 * @return int.
 */
int found_cli_and_exec(int cli_socket, char *command);

void execute_cli_cmd_g(client_t *cli, char *command);
int add_func(int a, int b);
void second_init_map(map_t *map, int x, int y, int width);
void init_map(map_t *map, int width, int height);
int initialize_map(int width, int height);
void display(struct map_s *map);

int place_mendiane_on_map(map_t *map);
int place_sibur_on_map(map_t *map);
int place_deraumere_on_map(map_t *map);
int place_linemate_on_map(map_t *map);
int place_food_on_map(map_t *map);
void place_egg_on_map_bis(int team_index, map_t *map);
void add_egg_to_team_ll(team_t *team, int x, int y, int egg_id);

int place_phiras_on_map(map_t *map);
int place_thystame_on_map(map_t *map);

const char *get_north_pos(void);
const char *get_east_pos(void);
const char *get_south_pos(void);
const char *get_south_pos(void);
void player_spawn(client_t *cli, int team_index);

const char *get_food(void);
const char *get_linemate(void);
const char *get_deraumere(void);
const char *get_sibur(void);
const char *get_mendiane(void);
const char *get_phiras(void);
const char *get_thystame(void);
const char *get_egg(void);
const char *get_player(void);
const char *get_unknown(void);

void add_item_to_tiles(tile_t *tile, item_type_t type);
void place_randomly_items(map_t *map);
void display_item(items_t *item);
const char *get_items(item_type_t item);
item_type_t get_item_type(const char *item_name);
void delete_item_from_tiles(tile_t *tile, item_type_t type);
int checking_item_existence(items_t *item, item_type_t type);

void handle_player_death(client_t *cli);

bool is_gui(int cli_id);
int lower_cli_cd(client_t *cli);

void handle_egg_laying(void);
void client_fork_end(client_t *cli);

void move_player(client_t *cli, game_t *game);

int parse_cmd_table(char *cmd, int cli_socket, char *full_cmd);

waiting_client_t *get_waiting_client(server_t *server, char *team_name);
void look_orientation(int *x, int *y, position_t pos, int *stock);
int cross_items_ll(items_t *item, char **msg, size_t msg_size);
int check_to_append(int offset, char **msg, size_t msg_size, int cond);

void handle_renew_items(void);

void handle_end_game(void);

void handle_timeout_login(void);

#endif /* !SERVER_H_ */
