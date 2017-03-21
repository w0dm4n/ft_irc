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

typedef struct			s_client
{
	int					fd;
	struct sockaddr_in	in;
	struct s_client		*next;
	struct s_client		*prev;
	fd_set				read_fds;
	void				(*send)();
	int					connected;
	int					first;
	char				*remote_host;
	int					remote_port;
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
char					*get_client_addr(struct sockaddr_in client);
int						get_client_port(struct sockaddr_in client);
void					read_clients(t_server *server);
int						handle(char *buffer, t_client *client);
int						should_disconnect_client(char *buffer, \
	t_client *client);
void					welcome(t_client *client);

/*
** CLIENT
*/
char					*get_host(int argc, char **argv);
int						get_port(int argc, char **argv);
int						split_size(char **split);
int						check_adress_v4(char *adress);
void					print_prompt(t_client *client);
void					connection(char *host, int port);
int						connect_cmd(char **split);
int						disconnect(t_client	*client);

/*
** COMMANDS
*/
# define CONNECT_COMMAND "/connect"
# define CLEAR_COMMAND "/clear"
# define DISCONNECT_COMMAND "/disconnect"

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
** SERVER MESSAGE
*/
# define WELCOME_MESSAGE "WM\0"

/*
** CLIENT MESSAGE
*/
# define WELCOME_BACK "WB\0"
t_client	*g_clients;

#endif
