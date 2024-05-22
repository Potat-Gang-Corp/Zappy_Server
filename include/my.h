/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

int add_func(int a, int b);

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
 * @param int i index.
 * @param char *av represents the argument
 *
 * @details handle the port and initialize it in the struct
 * @return it exits because it's a void function it doesn't return anything
 */
void handle_p(int i, char *av);

 /**
 * @brief Function that check the existence of a definition for a flag
 * @param int i index position of the flag
 * @param int ac total number of arguments
 * @param char **av array that contains all of the arguments of the command line
 * 
 * @details The function checks if a flag has a definition and if it's definition is valid.
 * @return there is no return value unless if the function found a problem so it exit 84
 */

void check_av(int i, int ac, char **av);
void handle_x_y(int ac, int *i, char **av);
#endif /* !MY_H_ */
