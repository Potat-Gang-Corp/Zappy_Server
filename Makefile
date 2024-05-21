##
## EPITECH PROJECT, 2024
## ZAPPY
## File description:
## Makefile
##

NAME	=	zappy_server

CC	=	gcc

RM	=	rm -f

SRCS	=	($wildcard *.c)

OBJS	=	$(SRCS:.c=.o)

CFLAGS = -I./include -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)	

clean:
	$(RM) $(OBJS)
	$(RM) $(NAME)

fclean:	clean

re:	fclean all

.PHONY:	all clean fclean re
