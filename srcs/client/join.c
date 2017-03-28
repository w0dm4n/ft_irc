/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 06:06:19 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 06:06:20 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*serialize_join(char *data)
{
	char	*to_send;

	if (!(to_send = ft_strnew(CLIENT_READ)))
		return (NULL);
	ft_strcat(to_send, JOIN_MESSAGE);
	ft_strcat(to_send, ESCAPE_CHAR);
	ft_strcat(to_send, data);
	return (to_send);
}

int			in_channel(t_client *client, char *channel)
{
	channel = ft_strtolower(replace_newline(channel));
	if (client->channel != NULL)
		if (!ft_strcmp(client->channel->name, channel))
			return (TRUE);
	return (FALSE);
}

int			can_join(char *channel)
{
	if (ft_strlen(channel) < 1 || ft_strlen(channel) > 20)
	{
		printf("/join: Channel name must have between 1 and 20 characters\n");
		return (FALSE);
	}
	return (TRUE);
}

void		join(t_client *client, char *channel)
{
	if (client != NULL)
	{
		if (client->nickname != NULL && client->connected)
		{
			if (channel != NULL)
			{
				if (!in_channel(client, channel) && can_join(channel))
					client->send(client, client->serialize(JOIN_MESSAGE, \
						replace_newline(channel)));
			}
			else
				printf("/join: Syntax error (/join channel)\n");
		}
		else
		{
			printf("/join: You have to select a nickname before ");
			printf("joining a channel\n");
		}
	}
	else
		printf("/join: Please connect first !\n");
}
