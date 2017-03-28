/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:19:10 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/27 19:19:19 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*get_client_informations(t_client *client)
{
	char		*to_send;

	if (!(to_send = ft_strnew(1024)))
		return (NULL);
	ft_strcat(to_send, client->nickname);
	ft_strcat(to_send, ESCAPE_DATA);
	if (client->channel != NULL)
		ft_strcat(to_send, client->channel->name);
	return (to_send);
}

int			have_another_client(t_client *client)
{
	client = client->next;
	while (client)
	{
		if (client->nickname != NULL)
			return (TRUE);
		client = client->next;
	}
	return (FALSE);
}

void		who_is_online(t_client *client)
{
	char		*to_send;
	t_client	*clients;

	clients = g_clients;
	if (!(to_send = ft_strnew(CLIENT_READ)))
		return ;
	ft_strcat(to_send, WHO_MESSAGE);
	ft_strcat(to_send, ESCAPE_CHAR);
	while (clients)
	{
		if (clients->nickname != NULL)
		{
			ft_strcat(to_send, get_client_informations(clients));
			if (have_another_client(clients))
				ft_strcat(to_send, ESCAPE_CHAR);
		}
		clients = clients->next;
	}
	client->send(client, to_send);
}
