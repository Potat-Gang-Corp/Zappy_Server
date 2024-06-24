##
## EPITECH PROJECT, 2024
## ZAPPY
## File description:
## Makefile
##

NAME = zappy_server
TESTNAME = unit_tests

CC = gcc -g3
RM = rm -rf
ECHO = /bin/echo -e

GREEN    = \x1b[32m
CYAN     = \x1b[36m
RED      = \x1b[31m
JAUNE   = \x1b[33m
BLUE     = \x1b[34m
MAGENTA  = \x1b[35m
BOLD     = \x1b[1m
RESET    = \x1b[0m

SRC_DIR = src
SRCS = $(shell find $(SRC_DIR) -name '*.c')
TSRCS = $(wildcard tests/unit-tests/*.c)

SRCS_NO_MAIN = $(filter-out src/main.c, $(SRCS))

OBJS = $(SRCS:.c=.o)
OBJS_NO_MAIN = $(SRCS_NO_MAIN:.c=.o)
TOBJS = $(TSRCS:.c=.o)

CFLAGS = -I./include -Wall -Wextra -Werror --coverage
LDFLAGS = --coverage -lcriterion -lgcov -fprofile-arcs -ftest-coverage
GCOVRFLAGS = -r . --exclude 'tests/*'

all: $(NAME)

$(NAME): $(OBJS)
	@$(ECHO) "$(CYAN)$(BOLD)Linking $(NAME)...$(RESET)"
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)
	@$(ECHO) "$(GREEN)$(BOLD)$(NAME) compiled successfully!$(RESET)"

%.o: %.c
	@$(ECHO) "$(BLUE)$(BOLD)Compiling $<...$(RESET)"
	$(CC) -c -o $@ $< $(CFLAGS) > /dev/null

run: all
	@$(ECHO) "$(MAGENTA)$(BOLD)Running $(NAME)...$(RESET)"
	./$(NAME) -p 8080 -x 10 -y 10 -n name1 name2 -c 7 -f 300

$(TESTNAME): $(TOBJS) $(OBJS_NO_MAIN)
	@$(ECHO) "$(CYAN)$(BOLD)Linking $(TESTNAME)...$(RESET)"
	$(CC) -o $(TESTNAME) $(TOBJS) $(OBJS_NO_MAIN) $(CFLAGS) $(LDFLAGS)
	@$(ECHO) "$(GREEN)$(BOLD)$(TESTNAME) compiled successfully!$(RESET)"

tests_run: $(TESTNAME)
	@$(ECHO) "$(MAGENTA)$(BOLD)Running unit tests...$(RESET)"
	@./$(TESTNAME)
	@gcovr $(GCOVRFLAGS)
	@gcovr $(GCOVRFLAGS) --html --html-details -o tests/coverage.html
	@$(ECHO) "$(JAUNE)Coverage report generated in tests/coverage.html$(RESET)"

run_ftests: all
	@$(ECHO) "$(MAGENTA)$(BOLD)Running functional tests...$(RESET)"
	@./tests/functional-tests/tests.sh
	@./tests/functional-tests/tests_netcat.sh

clean:
	@$(ECHO) "$(RED)$(BOLD)Cleaning objects and temporary files...$(RESET)"
	$(RM) $(OBJS) $(TOBJS)
	find src -name '*.gc*' -exec $(RM) {} +
	$(RM) *.gc* $(TESTNAME) coverage.html
	$(RM) tests/*.gc*
	$(RM) tests/unit-tests/*.gc*
	$(RM) tests/coverage*
	$(RM) coverage*
	$(RM) coding-style-reports.log
	$(RM) vgcore.*
	$(RM) docs/
	$(RM) *.txt

fclean: clean
	@$(ECHO) "$(RED)$(BOLD)Cleaning executable...$(RESET)"
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re tests_run
