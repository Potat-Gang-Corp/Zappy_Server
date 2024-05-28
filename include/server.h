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
int init_socket(void);
int init_struct_addr(void);
int init_server_launch(void);

//run_server.c
int run_server(void);
void handle_sigint(int sig);

//accept_cli.c
int accept_new_client(void);
int accept_loop(int new_socket);

//read_write_cmd.c
int handle_clients(void);
int process_cli_cmd(int cli_socket, int index);
char *read_cli_cmd(int cli_socket);

//select_cli.c
int select_loop(void);

//non_blocking_conf.c
int set_nonblocking(int fd) 

#endif /* !SERVER_H_ */
