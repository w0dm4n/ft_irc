/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 20:19:47 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/17 20:19:49 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void				disconnect_client(t_client *client)
{
	client->channel = NULL;
	remove_client(&g_clients, client);
	close(client->fd);
	printf("%sOne client disconnected (%s:%d)%s\n", KRED,\
			get_client_addr(client->in), get_client_port(client->in), \
			KNRM);
}

void				print_received(t_client *client, char *buffer)
{
	printf("%sReceived message from client (%s:%d): %s%s\n", KMAG, \
		get_client_addr(clients->in), get_client_port(clients->in), \
		buffer, KNRM);
}

void				read_clients(t_server *server)
{
	t_client	*clients;
	char		buffer[CLIENT_BUFFER];
	int			res;

	res = 0;
	clients = g_clients;
	ft_bzero(buffer, CLIENT_BUFFER);
	while (clients)
	{
		if (FD_ISSET(clients->fd, &server->read_fds))
		{
			res = recv(clients->fd, buffer, CLIENT_READ, 0);
			if (res > 0 && ft_strlen(buffer))
			{
				buffer[res] = '\0';
				print_received(clients, buffer);
				if (ft_strlen(buffer) <= MAX_PACKET_SIZE)
					handle(decrypt_message(buffer), clients);
				ft_bzero(buffer, CLIENT_BUFFER);
			}
			else
				disconnect_client(clients);
		}
		clients = clients->next;
	}
}

void				accept_client(t_server *server)
{
	t_client	*client;
	socklen_t	length;

	length = 0;
	if (FD_ISSET(server->fd, &server->read_fds))
	{
		if (!(client = alloc_new_client()))
			return ;
		length = sizeof(client->in);
		if ((client->fd = \
			accept(server->fd, (struct sockaddr*)&client->in, &length)) == -1)
			print_error("Can't accept client connection", 0);
		else
		{
			printf("%sNew client connected from %s:%d%s\n", KGRN, \
			get_client_addr(client->in), get_client_port(client->in), \
			KNRM);
			add_client(client);
			client->send(client, WELCOME_MESSAGE);
		}
	}
}
