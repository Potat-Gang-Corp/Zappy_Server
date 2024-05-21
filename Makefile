## EPITECH PROJECT, 2024
## ZAPPY
## File description:
## Makefile
##

NAME = zappy_server
TESTNAME = unit_tests

CC = gcc
RM = rm -f

SRCS = $(wildcard src/*.c)
TSRCS = $(wildcard tests/unit-tests/*.c)

SRCS_NO_MAIN = $(filter-out src/main.c, $(SRCS))

OBJS = $(SRCS:.c=.o)
OBJS_NO_MAIN = $(SRCS_NO_MAIN:.c=.o)
TOBJS = $(TSRCS:.c=.o)

CFLAGS = -I./include -Wall -Wextra -Werror --coverage
LDFLAGS = --coverage -lcriterion

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(TESTNAME): $(TOBJS) $(OBJS_NO_MAIN)
	$(CC) -o $(TESTNAME) $(TOBJS) $(OBJS_NO_MAIN) $(CFLAGS) $(LDFLAGS)

tests_run: $(TESTNAME)
	./$(TESTNAME)
	@gcovr -r . --exclude 'tests/*'
	@gcovr -r . --exclude 'tests/*' --html --html-details -o tests/coverage.html
	@echo "Coverage report generated in coverage.html"

clean:
	$(RM) $(OBJS) $(TOBJS)
	$(RM) src/*.gc*
	$(RM) *.gc* $(TESTNAME) coverage.html
	$(RM) tests/*.gc*
	$(RM) tests/unit-tests/*.gc*
	$(RM) tests/coverage*
	$(RM) coverage*

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re tests_run
