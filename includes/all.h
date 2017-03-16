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

void			print_error(char *msg, int exit_code);

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

#endif
