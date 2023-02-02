SRCS =	srcs/main.cpp\
		srcs/cmds/cmd_join.cpp\
		srcs/cmds/cmd_kick.cpp\
		srcs/cmds/cmd_nick.cpp\
		srcs/cmds/cmd_privmsg.cpp\
		srcs/cmds/cmd_pingpong.cpp\
		srcs/cmds/cmd_part.cpp\
		srcs/cmds/cmd_topic.cpp\
		srcs/cmds/cmd_mode.cpp\
		srcs/cmds/cmd_oper.cpp\
		srcs/cmds/cmd_kill.cpp\
		srcs/Channel.cpp\
		srcs/send_rpl_err.cpp\
		srcs/send.cpp\
		srcs/Server.cpp\
		srcs/User.cpp\
		srcs/utils.cpp\

OBJS =	${SRCS:.cpp=.o}

INCLUDES =	includes/Channel.hpp\
			includes/Command.hpp\
			includes/RPL_ERR.hpp\
			includes/Server.hpp\
			includes/User.hpp\
			includes/utils.hpp\
			includes/main.hpp\

CC =	c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -I includes

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
