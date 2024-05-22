/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** handle_flags
*/

#ifndef HANDLE_FLAGS_H_
    #define HANDLE_FLAGS_H_
/**
* @file handle_flags.h
* @brief Contains definitions of the flags handling functions
*/
///////////////////////handle_flags.c///////////////////////
/**
 * @brief Function that allows to handle the flags.
 * @param ac number of arguments.
 * @param av arguments.
 *
 * @details will treat the flags acording to the arguments.
 * @return return 0 if everything's good or 84 if an error occured.
 */
int handle_flags(int argc, char **argv);

/**
 * @brief Function that displays the help text
 * @param void
 *
 * @details display_help is full of printfs that display the usage of the bin
 * @return it exits because it's a void function it doesn't return anything
 */
void display_help(void);

/**
 * @brief Function that handles the port
 * @param char *av represents the argument
 *
 * @details handle the port and initialize it in the struct
 * @return it exits because it's a void function it doesn't return anything
 */
void handle_p(char *av);

/**
* @brief Function that check the existence of a definition for a flag
* @param int i index position of the flag
* @param int ac total number of arguments
* @param char **av array that contains all of the arguments of the command line
*
* @details The function checks if a flag has a definition and if it's
 definition is valid.
* @return there is no return value unless if the function found a problem so it
 exit 84
*/
void check_av(int i, int ac, char **av);

///////////////////////handle_x_y.c///////////////////////
/**
* @brief Function that check the existence of a definition for x flag
* @param char *av string that contains the argument
*
* @details The function gets the width of the world
* @return void
*/
void handle_x(char *av);
/**
* @brief Function that check the existence of a definition for y flag
* @param char *av string that contains the argument
*
* @details The function gets the height of the world
* @return void
*/
void handle_y(char *av);
/**
* @brief Function that check the existence of a definition for y and x flags
* @param int ac total number of arguments
* @param int *i index position of the flag
* @param char **av array that contains all of the arguments of the command line
* @param int *fp pointer to the flags_present variable
*
* @details The function gets the width and height of the world
* @return void unless the function found a problem so it exit 84
*/
void handle_x_y(int ac, int *i, char **av, int *fp);

///////////////////////handle_n_c_f.c///////////////////////
/**
* @brief Function that check the existence of a definition for n flag
* @param char *av string that contains the argument
* @param int *fp pointer to the flags_present variable
* @param int ac total number of arguments
* @param int *i index position of the flag
*
* @details The function gets the teams names
* @return void
*/
void handle_n(int ac, int *i, char **av, int *fp);
/**
* @brief Function that check the existence of a definition for c flag
* @param char *av string that contains the argument
* @param int *fp pointer to the flags_present variable
*
* @details The function gets the number of clients per team
* @return void
*/
void handle_c(char *av, int *fp);
/**
* @brief Function that check the existence of a definition for f flag
* @param char *av string that contains the argument
* @param int *fp pointer to the flags_present variable
*
* @details The function gets the frequency
* @return void
*/
void handle_f(char *av, int *fp);
/**
* @brief Function that check the existence of a definition for n, c and f flags
* @param int ac total number of arguments
* @param int *i index position of the flag
* @param char **av array that contains all of the arguments of the command line
* @param int *fp pointer to the flags_present variable
*
* @details The function gets the teams names, the nb of clients and frequency
* @return void unless the function found a problem so it exit 84
*/
void handle_n_c_f(int ac, int *i, char **av, int *fp);

#endif /* !HANDLE_FLAGS_H_ */
