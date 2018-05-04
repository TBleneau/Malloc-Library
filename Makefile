##
## EPITECH PROJECT, 2018
## malloc
## File description:
## malloc
##

NAME		= libmy_malloc.so

SRCS		= malloc.c		\
		  make_call_sbrk.c	\
		  free.c		\
		  realloc.c		\
		  show_alloc_mem.c	\
		  calloc.c

OBJS		= $(addprefix sources/, $(SRCS:.c=.o))

CC		= gcc

RM		= rm -f

CFLAGS		= -I includes/
CFLAGS		+= -fpic
CFLAGS		+= -Wall -Wextra
CFLAGS		+= -std=gnu99

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(CFLAGS) -shared $(OBJS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
