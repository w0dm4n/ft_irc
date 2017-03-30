/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:58:54 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/16 14:59:37 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_server		*get_socket(int port)
{
	t_server	*server;
	int			opt;

	opt = TRUE;
	if (!(server = (t_server*)malloc(sizeof(struct s_server))))
		return (NULL);
	if ((server->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		print_error("Can't create socket", -1);
	server->in.sin_family = AF_INET;
	server->in.sin_addr.s_addr = INADDR_ANY;
	server->in.sin_port = htons(port);
	if ((setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, \
		sizeof(opt))) < 0)
		print_error("Can't allow multiple connection on socket", -1);
	if ((bind(server->fd, (struct sockaddr *)&server->in, \
		sizeof(server->in))) < 0)
		print_error("Can't bind socket", -1);
	if ((listen(server->fd, 3)) == -1)
		print_error("Can't listen the socket", -1);
	printf("Server launched on port %d, waiting for connections...\n", port);
	return (server);
}

int				add_clients_fd(t_server *server)
{
	t_client	*clients;
	int			max_fd;

	max_fd = server->fd;
	clients = g_clients;
	while (clients)
	{
		FD_SET(clients->fd, &server->read_fds);
		if (clients->fd > max_fd)
			max_fd = clients->fd;
		clients = clients->next;
	}
	return (max_fd + 1);
}

void			init_server(int port)
{
	t_server	*server;
	int			res;
	int			max_fd;

	server = get_socket(port);
	while (TRUE)
	{
		FD_ZERO(&server->read_fds);
		FD_SET(server->fd, &server->read_fds);
		max_fd = add_clients_fd(server);
		if ((res = select(max_fd, &server->read_fds, NULL, NULL, NULL)) < 0)
			print_error("An error occured with the select", -1);
		accept_client(server);
		read_clients(server);
	}
}

int				main(int argc, char **argv)
{
	printf("%s'########:'########::::::::::'####:'########:::'######::\n", \
		KCYN);
	printf("##.....::... ##..:::::::::::. ##:: ##.... ##:'##... ##:\n");
	printf("##:::::::::: ##:::::::::::::: ##:: ##:::: ##: ##:::..::\n");
	printf("######:::::: ##:::::::::::::: ##:: ########:: ##:::::::\n");
	printf("##...::::::: ##:::::::::::::: ##:: ##.. ##::: ##:::::::\n");
	printf("##:::::::::: ##:::::::::::::: ##:: ##::. ##:: ##::: ##:\n");
	printf("##:::::::::: ##::::'#######:'####: ##:::. ##:. ######::\n");
	printf("..:::::::::::..:::::.......::....::..:::::..:::......:::%s\n", \
		KNRM);
	if (argc == 2)
		init_server(ft_atoi(argv[1]));
	else
		printf("./serveur: Syntax error (./serveur port)\n");
}
