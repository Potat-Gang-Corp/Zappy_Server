/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

//init_server.c
int init_server(void);
int init_server_bis(void);
int init_socket(void);
int init_struct_addr(void);
int init_server_launch(void);
int init_server_listen(void);

//run_server.c
int run_server(void);
void handle_sigint(int sig);

//accept_cli.c
int accept_new_client(void);
int com_with_cli(int new_socket);
int following(char *team_name, int new_socket);
int accept_loop(int new_socket, int nb_joueur, int index);
int add_to_waiting_list(int new_socket, const char *team);
int add_to_ll(int new_socket, int index);
int add_to_ll_bis(int new_socket, int index);
int init_ll(int new_socket, int index);

//read_write_cmd.c
int handle_clients(void);
int cond_of_loop(int cli_socket, int index);
int handle_cmd(int cli_socket, char *cmd);
int find_socket(int cli_socket, struct client_s *cli, char *cmd);
int add_command_to_list(int cli_id, const char *cmd);
int process_cli_cmd(int cli_socket, int index);
char *read_cli_cmd(int cli_socket);

//select_cli.c
int select_loop(void);
int select_function(void);

//non_blocking_conf.c
int set_nonblocking(int fd);

#endif /* !SERVER_H_ */
