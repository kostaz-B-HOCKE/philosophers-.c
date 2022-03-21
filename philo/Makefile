NAME		= Philosofers

SRC			=	src/main.c  src/validat.c src/info.c src/utilites.c src/action.c src/pthread.c


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
			@gcc -o ${NAME} ${OBJ}


clean:
			@$(RM) $(OBJ)


fclean:		clean
			@$(RM) $(NAME)


re:		fclean all

#.PONY		all clean fclean re
