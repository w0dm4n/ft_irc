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

void			send_data(t_client *client, char *msg)
{
	if (client->fd)
		write(client->fd, msg, ft_strlen(msg));
}

t_client		*alloc_new_client(void)
{
	t_client	*client;

	if (!(client = (t_client*)malloc(sizeof(t_client))))
		return (NULL);
	client->prev = NULL;
	client->next = NULL;
	client->fd = 0;
	client->send = send_data;
	return (client);
}

void	remove_client(t_client **ptr, t_client *map)
{
	t_client	tmp;

	while ((*ptr) != NULL)
	{
		if ((*ptr) == map)
		{
			tmp = **ptr;
			*ptr = (*ptr)->next;
		}
		else
			ptr = &((*ptr)->next);
	}
}

void			add_client(t_client *client)
{
	t_client	*clients;

	clients = g_clients;
	if (clients)
	{
		while (clients->next)
			clients = clients->next;
		clients->next = client;
		client->prev = clients;
	}
	else
		g_clients = client;
}

void			disconnect_client(t_client *client)
{
	remove_client(&g_clients, client);
	close(client->fd);
	printf("One client disconnected (%s:%d)\n", \
			get_client_addr(client->in), get_client_port(client->in));
}

void			read_clients(t_server *server)
{
	t_client	*clients;
	char		buffer[CLIENT_BUFFER];
	int			res;


	res = 0;
	clients = g_clients;
	while (clients)
	{
		if (FD_ISSET(clients->fd, &server->read_fds))
		{
			res = recv(clients->fd, buffer, CLIENT_READ, 0);
			if (res > 0)
			{
				printf("Received message from client (%s:%d): %s\n", \
				get_client_addr(clients->in), get_client_port(clients->in), buffer);
				handle(buffer);
			}
			else
				disconnect_client(clients);
		}
		clients = clients->next;
	}
}

void			accept_client(t_server *server)
{
	t_client	*client;
	socklen_t	length;

	length = 0;
	if (FD_ISSET(server->fd, &server->read_fds))
	{
		if (!(client = alloc_new_client()))
			return ;
		length = sizeof(client->in);
		if ((client->fd = accept(server->fd, (struct sockaddr*)&client->in, &length)) == -1)
			print_error("Can't accept client connection", 0);
		else
		{
			printf("New client connected from %s:%d\n", \
			get_client_addr(client->in), get_client_port(client->in));
			add_client(client);
			client->send(client, WELCOME_MESSAGE);
		}
	}
}
