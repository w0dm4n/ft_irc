/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 05:57:28 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 05:57:29 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_channel		*get_channel(char *name)
{
	t_channel	*channel;

	if (!(channel = (t_channel*)malloc(sizeof(struct s_channel))))
		return (NULL);
	channel->prev = NULL;
	channel->next = NULL;
	channel->name = name;
	return (channel);
}

void			set_channel(char *channel, t_client *client)
{
	if (channel != NULL)
	{
		client->channel = get_channel(channel);
		if (client->channel != NULL)
		{
			printf("You're now in the channel %s\n", client->channel->name);
			print_prompt(client);
		}
	}
}

void			channel_message(char *author, char *msg, t_client *client)
{
	if (client != NULL && client->channel != NULL)
	{
		if (author != NULL && msg != NULL)
		{
			if (ft_strcmp(client->nickname, author))
				ft_putstr("\n");
			printf("[%s%s%s] [%s%s%s]: %s\n", \
				KYEL, author, KNRM, KRED, \
				client->channel->name, KNRM, msg);
			print_prompt(client);
		}
	}
}

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

int				talk_channel(char *msg, t_client *client, t_channel *channel)
{
	char	*to_send;

	to_send = NULL;
	if (msg != NULL && ft_strlen(replace_newline(msg)) > 0)
	{
		msg = replace_newline(msg);
		if (!(to_send = ft_strnew(CLIENT_READ)))
			return (TRUE);
		ft_strcat(to_send, channel->name);
		ft_strcat(to_send, ESCAPE_CHAR);
		ft_strcat(to_send, msg);
		client->send(client, client->serialize(CHANNEL_MESSAGE, to_send));
		return (FALSE);
		ft_strdel(&to_send);
	}
	return (TRUE);
}
