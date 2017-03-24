/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talk_channel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 02:16:37 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/24 02:16:45 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char			*serialize_channel_msg(char *data)
{
	char	*to_send;

	if (!(to_send = ft_strnew(CLIENT_READ)))
		return (NULL);
	ft_strcat(to_send, CHANNEL_MESSAGE);
	ft_strcat(to_send, ESCAPE_CHAR);
	ft_strcat(to_send, data);
	return (to_send);
}

void		send_to_channel(t_channel *channel, char *msg)
{
	t_client	*clients;

	clients = g_clients;
	while (clients)
	{
		if (clients->channel == channel)
			clients->send(clients, clients->serialize(CHANNEL_MESSAGE, msg));
		clients = clients->next;
	}
}

int			not_only_space(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		if (msg[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void		notif_channel(t_channel *channel, t_client *client)
{
	t_client	*clients;
	char		*to_send;

	if (!(to_send = ft_strnew(CLIENT_READ)))
		return ;
	ft_strcat(to_send, client->nickname);
	ft_strcat(to_send, " has joined the channel.");
	clients = g_clients;
	while (clients)
	{
		if (clients->channel == channel && clients != client)
		{
			clients->send(clients, \
			clients->serialize(INFO_MESSAGE, \
				to_send));
		}
		clients = clients->next;
	}
	ft_strdel(&to_send);
}

void		talk_channel_server(char **data, t_client *client, t_channel *channel)
{
	char	*to_send;

	to_send = NULL;
	if (client != NULL && client->channel != NULL \
		&& data[1] != NULL && data[2] != NULL)
	{
		if (not_only_space(data[2]) == FALSE)
		{
			if (!(to_send = ft_strnew(CLIENT_READ)))
				return ;
			ft_strcat(to_send, client->nickname);
			ft_strcat(to_send, ESCAPE_CHAR);
			ft_strcat(to_send, data[2]);
			printf("Chat message: [%s] from user [%s] on channel [%s] sent !\n", \
			 data[2], client->nickname, channel->name);
			send_to_channel(channel, to_send);
			ft_strdel(&to_send);
		}
		else
			client->send(client, \
			client->serialize(INFO_MESSAGE, \
				"Hey ! Send me a real message..."));
	}
}
