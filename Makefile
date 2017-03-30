# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2017/03/24 04:06:43 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVEUR	=	serveur
NAME_CLIENT     =   client
NAME		=   ft_irc
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-24-$(LENGTHNAME)"|bc)

CC			=	gcc 
#FLAGS		=	-Wall -Wextra -Werror -O3
FLAGS       =  -ggdb
FLAGS_O		=	

SRCDIR_SERVEUR		=	srcs/server/
SRCDIR_CLIENT			=	srcs/client/

OBJDIR_SERVEUR		=	objs/server/
OBJDIR_CLIENT			=	objs/client/

INCDIR				=	includes/
LIBFT_DIR			=	libft/
LIBFT_LIB			=	$(LIBFT_DIR)libft.a

SRCBASE_SERVEUR	=	\
					server.c \
					error.c  \
					client.c \
					handler.c \
					welcome.c \
					encryption.c \
					utils.c   \
					nickname.c \
					serializer.c \
					join.c     \
					channel.c  \
					talk_channel.c \
					who.c      \
					leave.c    \
					pm.c

SRCBASE_CLIENT		=	\
					client.c \
					error.c  \
					host.c	 \
					utils.c  \
					handler.c \
					connect.c \
					prompt.c  \
					disconnect.c \
					help.c    \
					encryption.c \
					nickname.c \
					serializer.c \
					from_server.c \
					channel.c \
					join.c    \
					who.c \
					leave.c \
					private_message.c \
					send.c

INCS		=	$(addprefix $(INCDIR), $(INCBASE))

SRCS_SERVEUR		=	$(addprefix $(SRCDIR_SERVEUR), $(SRCBASE_SERVEUR))
OBJS_SERVEUR		=	$(addprefix $(OBJDIR_SERVEUR), $(SRCBASE_SERVEUR:.c=.o))

SRCS_CLIENT		=	$(addprefix $(SRCDIR_CLIENT), $(SRCBASE_CLIENT))
OBJS_CLIENT		=	$(addprefix $(OBJDIR_CLIENT), $(SRCBASE_CLIENT:.c=.o))

.SILENT:

all:		$(NAME)

$(NAME):
	if test -f $(NAME_SERVEUR) && test -f $(NAME_CLIENT) ; then					\
		echo "make: Nothing to be done for \`all\`.";				        \
	else																	\
		make server && make client && 											\
		echo "\r\033[38;5;184m👥  AUTHOR(s): \033[0m\033[K" && 		\
		echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K" && \
		echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K";		\
	fi

$(OBJDIR_SERVEUR):
	mkdir -p $(OBJDIR_SERVEUR)
	mkdir -p $(dir $(OBJS_SERVEUR))

$(OBJDIR_SERVEUR)%.o : $(SRCDIR_SERVEUR)%.c | $(OBJDIR_SERVEUR)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(LIBFT_DIR)$(INCDIR)											\
		-I $(INCDIR)
	printf "\r\033[38;5;11m%s%*.*s\033[0m\033[K"							\
		"⌛  MAKE          wait ..."										\
		$(MAX_COLS) $(MAX_COLS) "($(@))"

$(OBJDIR_CLIENT):
	mkdir -p $(OBJDIR_CLIENT)
	mkdir -p $(dir $(OBJS_CLIENT))

$(OBJDIR_CLIENT)%.o : $(SRCDIR_CLIENT)%.c | $(OBJDIR_CLIENT)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(LIBFT_DIR)$(INCDIR)											\
		-I $(INCDIR)
	printf "\r\033[38;5;11m%s%*.*s\033[0m\033[K"							\
		"⌛  MAKE   pls    wait ..."											\
		$(MAX_COLS) $(MAX_COLS) "($(@))"

fcleanlib:	fclean
	make -C $(LIBFT_DIR) fclean

re:			fclean all

relib:		fclean fcleanlib all

.PHONY:		fclean fcleanlib clean re relib

client: $(OBJDIR_CLIENT) $(OBJS_CLIENT)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_CLIENT) $(OBJS_CLIENT) $(LIBFT_LIB)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_CLIENT)"

server: $(OBJDIR_SERVEUR) $(OBJS_SERVEUR)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_SERVEUR) $(OBJS_SERVEUR) $(LIBFT_LIB)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_SERVEUR)"

clean:
	printf "\r\033[38;5;11m⌛  CLEAN  $(NAME_SERVEUR) pls wait ...\033[0m\033[K"
	if [[ `rm -R $(OBJDIR_SERVEUR) &> /dev/null 2>&1; echo $$?` == "0" ]]; then	\
		echo "\r\033[38;5;124m📕  CLEAN  $(NAME_SERVEUR)\033[0m\033[K";			\
	else																	    \
		printf "\r";														    \
	fi
	printf "\r\033[38;5;11m⌛  CLEAN  $(NAME_CLIENT) pls wait ...\033[0m\033[K"
	if [[ `rm -R $(OBJDIR_CLIENT) &> /dev/null 2>&1; echo $$?` == "0" ]]; then	\
		echo "\r\033[38;5;124m📕  CLEAN  $(NAME_CLIENT)\033[0m\033[K";			\
	else																	\
		printf "\r";														\
	fi

fclean:		clean
	printf "\r\033[38;5;11m⌛  FCLEAN $(NAME_SERVEUR) pls wait ...\033[0m\033[K"
	if [[ `rm $(NAME_SERVEUR) &> /dev/null 2>&1; echo $$?` == "0" ]]; then		\
		echo "\r\033[38;5;124m📕  FCLEAN $(NAME_SERVEUR)\033[0m\033[K";			\
	else																	    \
		printf "\r";														    \
	fi
	printf "\r\033[38;5;11m⌛  FCLEAN $(NAME_CLIENT) pls wait ...\033[0m\033[K"
	if [[ `rm $(NAME_CLIENT) &> /dev/null 2>&1; echo $$?` == "0" ]]; then		    \
		echo "\r\033[38;5;124m📕  FCLEAN $(NAME_CLIENT)\033[0m\033[K";			    \
	else																	    \
		printf "\r";														    \
	fi

-include $(OBJS:.o=.d)
