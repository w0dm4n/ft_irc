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

typedef struct			s_client
{
	int					fd;
	struct sockaddr_in	in;
	struct s_client		*next;
	struct s_client		*prev;
}						t_client;

typedef struct			s_server
{
	int					fd;
	struct sockaddr_in	in;
	fd_set				read_fds;
}						t_server;

void			print_error(char *msg, int exit_code);
void			accept_client(t_server *server);
char			*get_client_addr(struct sockaddr_in client);
int				get_client_port(struct sockaddr_in client);
void			read_clients(t_server *server);
/*
ERRNO DEFINITIONS
*/
# define PERMISSION_DENIED 13
# define ALREADY_IN_USE 48

/*
SOCKET SIZE DEFINE
*/
# define CLIENT_BUFFER 4096
# define CLIENT_READ 1024

t_client	*g_clients;

#endif
