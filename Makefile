SRCS =	main.cpp\
		User.cpp\
		Command.cpp\
		Server.cpp\
		send_rpl_err.cpp\
		Channel.cpp\
		utils.cpp

OBJS =	${SRCS:.cpp=.o}

INCLUDES =	User.hpp\
			Command.hpp\
			Server.hpp\
			RPL_ERR.hpp\
			Channel.hpp

CC =	c++

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -static-libsan -g3 -std=c++98 -I includes

NAME =	server

RM =	rm -rf

%.o:	%.cpp ${INCLUDES}
		${CC} ${CFLAGS} -c $< -o $@

all:	${NAME} Makefile

${NAME}:	${OBJS}	Makefile
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
