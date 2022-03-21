NAME		= philo_bonus

SRC_DIR		= src_bonus/

SRC			= $(addprefix $(SRC_DIR), main.c  validat.c  utilites.c init.c atc.c)



#SRC			=	src/test1.c

#SRC			= src/$(SRCC)

OBJ			= $(SRC:.c=.o)

RM			= /bin/rm -f

CFLAGS 		=
#CFLAGS 		= -Wall -Wextra -Werror

CC 			= gcc

.c.o:
			@$(CC) -c $< -o $(<:.c=.o)


all:		${NAME}


$(NAME):	${OBJ}
			@gcc -Wall -Wextra -Werror -o ${NAME} ${OBJ}

clean:
			@$(RM) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re:		fclean all

#.PONY		all clean fclean re
