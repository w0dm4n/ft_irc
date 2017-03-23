/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 02:47:43 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 02:47:44 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*serialize_nick(char *data)
{
	char	*to_send;

	if (!(to_send = ft_strnew(CLIENT_READ)))
		return (NULL);
	ft_strcat(to_send, NICK_MESSAGE);
	ft_strcat(to_send, ESCAPE_CHAR);
	ft_strcat(to_send, data);
	return (to_send);
}

int			nickname_available(char *name)
{
	t_client	*clients;

	clients = g_clients;
	while (clients)
	{
		if (clients->nickname != NULL && !ft_strcmp(clients->nickname, name))
			return (FALSE);
		clients = clients->next;
	}
	return (TRUE);
}

void		nickname_server(char *nickname, t_client *client)
{
	if (nickname != NULL && nickname_available(nickname) == TRUE)
	{
		if (ft_strlen(nickname) >= 2 && ft_strlen(nickname) <= 9)
		{
			client->nickname = nickname;
			client->send(client, client->serialize(NICK_MESSAGE, nickname));
		}
		else
			client->send(client, \
				client->serialize(INFO_MESSAGE, WRONG_NICK_FORMAT));
	}
	else
		client->send(client, \
				client->serialize(INFO_MESSAGE, NICK_NOT_AVAILABLE));
}
