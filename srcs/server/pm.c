/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:53:53 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/30 10:53:55 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int			user_online(char *nickname, t_client *client)
{
	t_client	*clients;

	clients = g_clients;
	while (clients)
	{
		if (clients->nickname != NULL)
		{
			if (!ft_strcmp(ft_strtolower(clients->nickname), nickname))
				return (TRUE);
		}
		clients = clients->next;
	}
	client->send(client, \
		client->serialize(INFO_MESSAGE, \
			"This user doesn't exist or is not online"));
	return (FALSE);
}

char		*serialize_mp(char *data)
{
	char	*to_send;

	if (!(to_send = ft_strnew(CLIENT_READ)))
		return (NULL);
	ft_strcat(to_send, MP_MESSAGE);
	ft_strcat(to_send, ESCAPE_CHAR);
	ft_strcat(to_send, data);
	return (to_send);
}

void		send_message(char *user, char *msg, t_client *client)
{
	char		*data;
	t_client	*target;

	target = NULL;
	data = NULL;
	if (user != NULL && msg != NULL)
	{
		if (!(target = get_client_by_nickname(user)))
			return ;
		if (!(data = ft_strnew(CLIENT_READ)))
			return ;
		ft_strcat(data, client->nickname);
		ft_strcat(data, ESCAPE_DATA);
		ft_strcat(data, msg);
		target->send(target, target->serialize(MP_MESSAGE, data));
		client->send(client, client->serialize(MP_MESSAGE, data));
		ft_strdel(&data);
	}
}

void		pm_server(t_client *client, char *data)
{
	char	**split;

	split = NULL;
	if (data != NULL)
	{
		split = ft_strsplit(data, ESCAPE_DATA[0]);
		if (split[0] != NULL && split[1] != NULL)
		{
			if (ft_strcmp(ft_strtolower(client->nickname), split[0]))
			{
				if (user_online(split[0], client))
					send_message(split[0], split[1], client);
			}
			else
				client->send(client, \
					client->serialize(INFO_MESSAGE, \
				"Hey ! you can't send a message to yourself..."));
		}
	}
}
