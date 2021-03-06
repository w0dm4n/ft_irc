/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 03:12:19 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/19 03:12:23 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include "../libft/includes/libft.h"
# include <sys/socket.h>
# include <sys/types.h>
# include <fcntl.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/mman.h>
# include <unistd.h>
# include <errno.h>
# define TRUE 1
# define FALSE 0
# define MAX_PORT 65535
# define ENCRYPTION_KEY "@#$KGERNGJR$#^#$#@(CG@$)+="
# define MAX_PACKET_SIZE 512

/*
** COLORS
*/
# define KNRM  "\e[38;05;194m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

/*
** INFOS MESSAGES
*/
# define WRONG_NICK_FORMAT1 "Your nickname need to "
# define WRONG_NICK_FORMAT2 "have between 2 and 9 characters\0"
# define WRONG_NICK_FORMAT WRONG_NICK_FORMAT1 WRONG_NICK_FORMAT2

# define NICK_NOT_AVAILABLE1 "This nickname is already taken, "
# define NICK_NOT_AVAILABLE2 "please chose another oner !\0"
# define NICK_NOT_AVAILABLE NICK_NOT_AVAILABLE1 NICK_NOT_AVAILABLE2

typedef struct			s_channel
{
	char				*name;
	struct s_channel	*next;
	struct s_channel	*prev;
}						t_channel;

typedef struct			s_client
{
	int					fd;
	struct sockaddr_in	in;
	struct s_client		*next;
	struct s_client		*prev;
	fd_set				read_fds;
	void				(*send)();
	char				*(*serialize)(char*, char*);
	int					connected;
	int					first;
	char				*remote_host;
	int					remote_port;
	char				*nickname;
	t_channel			*channel;
	char				*packet_buffer;
}						t_client;

typedef struct			s_server
{
	int					fd;
	struct sockaddr_in	in;
	fd_set				read_fds;
}						t_server;

void					remove_client(t_client **ptr, t_client *map);

/*
** SERVER
*/
void					print_error(char *msg, int exit_code);
void					accept_client(t_server *server);
void					read_clients(t_server *server);
int						handle(char *buffer, t_client *client);
int						should_disconnect_client(char *buffer, \
	t_client *client);
void					welcome(t_client *client);
void					nickname_server(char *nickname, t_client *client);
void					join_server(char *channel, t_client *client);
void					join_channel(char *name, t_client *client, \
	t_channel *channel);
void					talk_channel_server(char **data, \
	t_client *client, t_channel *channel);
void					notif_channel(t_channel *channel, t_client *client);
void					who_is_online(t_client *client);
void					leave_server(t_client *client);
char					*serialize_leaved(void);
void					pm_server(t_client *client, char *data);
t_client				*get_client_by_nickname(char *nickname);
char					*serialize_mp(char *data);
void					send_data(t_client *client, char *msg);
t_client				*alloc_new_client(void);
void					remove_client(t_client **ptr, t_client *map);
void					add_client(t_client *client);
void					check_handle(t_client *client, char *buffer);

/*
** CLIENT
*/
char					*get_host(int argc, char **argv);
int						get_port(int argc, char **argv);
int						split_size(char **split);
int						check_adress_v4(char *adress);
void					print_prompt(t_client *client);
void					connection(char *host, int port);
int						connect_cmd(char **split, t_client *client);
int						disconnect(t_client	*client);
int						help(void);
char					*replace_newline(char *str);
void					nickname(t_client *client, char *nickname);
void					from_server(char *msg, t_client *client);
void					set_nickname(char **data, t_client *client);
void					join(t_client *client, char *channel);
void					set_channel(char *channel, t_client *client);
int						talk_channel(char *msg, t_client *client, \
	t_channel *channel);
void					channel_message(char *author, char *msg, \
	t_client *client);
void					who(t_client *client);
void					who_from_server(char **data, t_client *client);
void					leave_channel(t_client *client);
void					leaved(t_client *client);
int						private_message(t_client *client, char **data, int i);
void					received_pm(char **data, t_client *client);
void					send_packet(t_client *client, char **split);
int						read_server(t_client *client);
void					check_welcome(char *message, t_client *client);
t_client				*get_client(char *host, int port);
void					send_data(t_client *client, char *msg);

/*
** BOTH SIDE
*/
char					*serializer(char *msg_type, char *data);
char					*serialize_nick(char *data);
char					*serialize_join(char *data);
char					*encrypt_message(char *msg);
char					*decrypt_message(char *crypted);
char					*int_to_hexastring(char c);
char					hexastring_to_int(char *s);
char					*serialize_join(char *data);
char					*serialize_channel_msg(char *data);
char					*serialize_who(void);
char					*serialize_leave(void);
char					*get_client_addr(struct sockaddr_in client);
int						get_client_port(struct sockaddr_in client);
/*
** COMMANDS
*/
# define CONNECT_COMMAND "/connect"
# define CLEAR_COMMAND "/clear"
# define DISCONNECT_COMMAND "/disconnect"
# define HELP_COMMAND "/help"
# define EXIT_COMMAND "/exit"
# define JOIN_COMMAND "/join"
# define NICK_COMMAND "/nick"
# define WHO_COMMAND "/who"
# define LEAVE_COMMAND "/leave"
# define SEND_COMMAND "/send"
# define MSG_COMMAND "/msg"

# define CLEAR_SCREEN "\033[2J"
# define RESET_CURSOR "\033[<1>C"

/*
** ERRNO DEFINITIONS
*/
# define PERMISSION_DENIED 13
# define ALREADY_IN_USE 48

/*
** SOCKET SIZE DEFINE
*/
# define CLIENT_BUFFER 8193
# define CLIENT_READ 8192

/*
** MESSAGE
*/
# define ESCAPE_CHAR "|"
# define ESCAPE_DATA ","
# define WELCOME_MESSAGE "WELCOME_MESSAGE\0"
# define WELCOME_BACK "WELCOME_BACK\0"
# define NICK_MESSAGE "NICKNAME\0"
# define INFO_MESSAGE "INFORMATIONS\0"
# define JOIN_MESSAGE "JOIN_CHANNEL\0"
# define CHANNEL_MESSAGE "CHANNEL_MESSAGE\0"
# define WHO_MESSAGE "WHO_MESSAGE\0"
# define LEAVE_MESSAGE "LEAVE_MESSAGE\0"
# define LEAVED_MESSAGE "LEAVED_MESSAGE\0"
# define MP_MESSAGE "MP_MESSAGE\0"

t_client	*g_clients;

#endif
