/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_extends.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:48:29 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/30 15:48:38 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void				send_data(t_client *client, char *msg)
{
	msg = encrypt_message(msg);
	if (client->fd)
	{
		write(client->fd, msg, ft_strlen(msg));
		printf("%sMessage sent to client (%s:%d): %s%s\n", KYEL, \
			get_client_addr(client->in), get_client_port(client->in), \
			msg, KNRM);
		ft_bzero(msg, ft_strlen(msg));
	}
}

t_client			*alloc_new_client(void)
{
	t_client	*client;

	if (!(client = (t_client*)malloc(sizeof(t_client))))
		return (NULL);
	client->prev = NULL;
	client->next = NULL;
	client->fd = 0;
	client->send = send_data;
	client->first = TRUE;
	client->nickname = NULL;
	client->serialize = serializer;
	client->channel = NULL;
	return (client);
}

void				remove_client(t_client **ptr, t_client *map)
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

void				add_client(t_client *client)
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
