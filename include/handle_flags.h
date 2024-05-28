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
 * @param int
 *
 * @details display_help is full of printfs that display the usage of the bin
 * @return it exits because it's a int function it doesn't return anything
 */
int display_help(void);
/**
 * @brief Function that allows to handle the flags.
 * @param int ac
 * @param char **av
 * @param int i
 * @param int flags_present
 *
 * @details will treat the flags acording to the arguments.
 * (it's the second part of handle_flags )
 * @return return 0 if everything's good or 84 if an error occured.
 */
int handle_flags_bis(int ac, char **av, int i, int *flags_present);

/**
 * @brief Function that handles the port
 * @param char *av represents the argument
 *
 * @details handle the port, check the validity of the given argument and
 *  initialize it in the struct.
 * @return it exits because it's a int function it doesn't return anything
 */
int handle_p(char *av);

/**
* @brief Function that check the existence of a definition for a flag
* @param int i index position of the flag
* @param int ac total number of arguments
* @param char **av array that contains all of the arguments of the command line
*
* @details The function checks if a flag has a definition and if it's
 definition is valid.
* @return there is no return value unless if the function found a problem so it
 return 84
*/
int check_av(int i, int ac, char **av);

///////////////////////handle_x_y.c///////////////////////
/**
* @brief Function that check the existence of a definition for x flag
* @param char *av string that contains the argument
*
* @details The function gets the width of the world, check the validity of the
 argument and initialize it in the structure.
* @return void
*/
int handle_x(char *av);
/**
* @brief Function that check the existence of a definition for y flag
* @param char *av string that contains the argument
*
* @details The function gets the height of the world, check the validity of
 the argument and initialize it in the structure.
* @return void
*/
int handle_y(char *av);
/**
* @brief Function that check the existence of a definition for y and x flags
* @param int ac total number of arguments
* @param int *i index position of the flag
* @param char **av array that contains all of the arguments of the command line
* @param int *fp pointer to the flags_present variable
*
* @details The function gets the width and height of the world
* @return int unless the function found a problem so it exit 84
*/
int handle_x_y(int ac, int *i, char **av, int *fp);

///////////////////////handle_n_c_f.c///////////////////////
/**
* @brief Function that check the existence of a definition for n flag
* @param char *av string that contains the argument
* @param int *fp pointer to the flags_present variable
* @param int ac total number of arguments
* @param int *i index position of the flag
*
* @details The function gets the teams names
* @return int
*/
int handle_n(int ac, int *i, char **av, int *fp);
/**
* @brief Function that check the existence of a definition for c flag
* @param char *av string that contains the argument
* @param int *fp pointer to the flags_present variable
*
* @details The function gets the number of clients per team, check the
 validity of the argument and initialize it in the structure.
* @return int
*/
int handle_c(char *av, int *fp);
/**
* @brief Function that check the existence of a definition for f flag
* @param char *av string that contains the argument
* @param int *fp pointer to the flags_present variable
*
* @details The function gets the frequency, check the validity of the argument
 and initialize it in the structure
* @return int
*/
int handle_f(char *av, int *fp);

/**
* @brief Function that check the existence of the definition for the n flag
* @param int ac total number of arguments
* @param int *i index position of the flag
* @param char **av array that contains all of the arguments of the command line
* @param int *fp pointer to the flags_present variable
*
* @details The function gets the teams names
* @return int 0 unless the function found a problem so it return 84
*/

int n_flag_detection(int ac, int *i, char **av, int *fp);

/**
* @brief Function that check the existence of a definition for n, c and f flags
* @param int ac total number of arguments
* @param int *i index position of the flag
* @param char **av array that contains all of the arguments of the command line
* @param int *fp pointer to the flags_present variable
*
* @details The function gets the teams names, the nb of clients and frequency
* @return int unless the function found a problem so it exit 84
*/
int handle_n_c_f(int ac, int *i, char **av, int *fp);

/**
* @brief Function that check the existence of a definition for n, c and f flags
* @param int flags_present reference value of flags present in command line
*
* @details The function gets the reference value to detect what are the flags
* present in the command line.
* @return value 0 if all of the required flags are presents, else return 84.
*/

int handle_fp(int flags_present);

#endif /* !HANDLE_FLAGS_H_ */
