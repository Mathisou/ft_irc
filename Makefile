SRCS =	main.cpp\
		cmds/cmd_join.cpp\
		cmds/cmd_nick.cpp\
		cmds/cmd_privmsg.cpp\
		Channel.cpp\
		Command.cpp\
		send_rpl_err.cpp\
		send.cpp\
		Server.cpp\
		User.cpp\
		utils.cpp\

OBJS =	${SRCS:.cpp=.o}

INCLUDES =	Channel.hpp\
			Command.hpp\
			RPL_ERR.hpp\
			Server.hpp\
			User.hpp\
			utils.hpp\
			main.hpp\

CC =	c++

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3 -std=c++98 -I includes

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
