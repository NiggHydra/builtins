PIPE	=	\

BUILTIN	=	main.c\
			utils.c
SIGNAL = signal.c\


				
SRCS = ${BUILTIN} ${SIGNAL}

CC		=	cc
CFLAGS		=	-Wall -Wextra -Werror -g 
LDFLAGS = -lreadline

NAME		=	minishell
OBJS		=	${SRCS:.c=.o}

all: ${NAME}

${NAME}:		${OBJS}
				${CC} ${CFLAGS} ${LDFLAGS} -o ${NAME} ${OBJS} -Llibft -lft

clean:
				rm -f ${OBJS}

fclean:			clean
				rm -f ${NAME}

re:				fclean all

.PHONY:			all  clean fclean re
