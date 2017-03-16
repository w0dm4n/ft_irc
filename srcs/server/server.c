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

char	*get_client_addr(struct sockaddr_in client)
{
	return (inet_ntoa(client.sin_addr));
}

int		get_client_port(struct sockaddr_in client)
{
	return (ntohs(client.sin_port));
}

void	read_client(struct sockaddr_in client, int fd)
{
	int 	res;
	char	*buffer;

	if (!(buffer = (char*)malloc(sizeof(char) * CLIENT_BUFFER)))
		return ;
	res = 0;
	while ((res = recv(fd, buffer, CLIENT_READ, 0)) > 0)
	{
		printf("Received message from client (%s:%d): %s\n", \
			get_client_addr(client), get_client_port(client), buffer);
		//if (!ft_strcmp(buffer, "cv?"))
		//	write(fd, "ui et toi", ft_strlen("ui et toi"));
		//write(fd, buffer, ft_strlen(buffer));
	}
	if (res <= 0)
	{
		close(fd);
		printf("One client disconnected (%s:%d)\n", \
			get_client_addr(client), get_client_port(client));
	}
}

void	accept_client(int socket_fd)
{
	struct sockaddr_in	client;
	socklen_t			client_len;
	int					client_fd;

	client_len = sizeof(client);
	client_fd = 0;
	if ((client_fd = accept(socket_fd, (struct sockaddr*)&client, &client_len)) == -1)
		print_error("Can't accept client connection", 0);
	else
	{
		printf("New client connected from %s:%d\n", \
			get_client_addr(client), get_client_port(client));
		read_client(client, client_fd);
	}
}

void	init_server(int port)
{
	struct sockaddr_in	server;
	int					socket_fd;
	struct sockaddr_in	client;

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		print_error("Can't create socket", -1);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port  = htons(port);
	if ((bind(socket_fd, (struct sockaddr *)&server, sizeof(server))) < 0)
		print_error("Can't bind socket", -1);
	if ((listen(socket_fd, 3)) == -1)
		print_error("Can't listen the socket", -1);
	printf("Server launched on port %d, waiting for connections...\n", port);
	accept_client(socket_fd);
	while (1)
		printf("??\n");
}

int		main(int argc, char **argv)
{
	if (argc == 2)
		init_server(ft_atoi(argv[1]));
	else
		printf("./serveur: Syntax error (./serveur port)\n");
	//while (1) ;
}
