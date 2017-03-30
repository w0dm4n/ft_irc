/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_extends.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:51:04 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/30 15:51:04 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		send_data(t_client *client, char *msg)
{
	msg = encrypt_message(msg);
	if (client->fd)
	{
		write(client->fd, msg, ft_strlen(msg));
		ft_bzero(msg, ft_strlen(msg));
	}
}

t_client	*get_client(char *host, int port)
{
	t_client	*client;

	if (!(client = (t_client*)malloc(sizeof(struct s_client))))
		return (NULL);
	client->fd = 0;
	client->next = NULL;
	client->prev = NULL;
	client->first = TRUE;
	client->send = send_data;
	client->remote_host = host;
	client->remote_port = port;
	client->serialize = serializer;
	client->nickname = NULL;
	client->channel = NULL;
	return (client);
}

void		check_welcome(char *message, t_client *client)
{
	if (ft_strcmp(message, WELCOME_MESSAGE))
	{
		printf("Invalid message received from the server: %s\n", message);
		disconnect(client);
	}
	else
	{
		printf("You're successfully connected to the server !\n");
		client->connected = TRUE;
		print_prompt(client);
		client->send(client, WELCOME_BACK);
	}
}

int			read_server(t_client *client)
{
	int			res;
	char		buffer[CLIENT_BUFFER];

	res = recv(client->fd, buffer, CLIENT_READ, 0);
	if (res > 0)
	{
		buffer[res] = '\0';
		if (client->first == TRUE)
		{
			check_welcome(decrypt_message(buffer), \
				client);
			client->first = FALSE;
		}
		else
			from_server(decrypt_message(buffer), client);
		ft_bzero(buffer, CLIENT_BUFFER);
	}
	return (res);
}
