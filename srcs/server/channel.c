/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 22:30:42 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 22:30:43 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_channel		*get_channels(void)
{
	static t_channel	*channels;

	if (channels == NULL)
	{
		if (!(channels = (t_channel*)malloc(sizeof(struct s_channel))))
			return (NULL);
		channels->prev = NULL;
		channels->next = NULL;
		channels->name = "accueil";
	}
	return (channels);
}

void			add_channel(t_channel *channel)
{
	t_channel	*channels;

	channel->name = ft_strtolower(channel->name);
	channels = get_channels();
	while (channels->next)
		channels = channels->next;
	channels->next = channel;
	channel->prev = channels;
}

t_channel		*new_channel(char *channel)
{
	t_channel	*new;
	t_channel	*channels;

	channels = get_channels();
	if (!(new = (t_channel*)malloc(sizeof(struct s_channel))))
			return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->name = channel;
	add_channel(new);
	return (new);
}

t_channel		*get_channel_by_name(char *name)
{
	t_channel	*channels;

	channels = get_channels();
	name = ft_strtolower(name);
	while (channels)
	{
		if (!ft_strcmp(channels->name, name))
			return (channels);
		channels = channels->next;
	}
	return (NULL);
}

void			join_channel(char *name, t_client *client)
{
	t_channel	*channel;

	channel = NULL;
	if (name != NULL && ft_strlen(name) > 0)
	{
		if ((channel = get_channel_by_name(name)) != NULL)
		{
			client->channel = channel;
			printf("Client (%s:%d - %s) added to existing channel %s\n", \
				get_client_addr(client->in), get_client_port(client->in), \
				client->nickname, name);
		}
		else
		{
			client->channel = new_channel(name);
			printf("Client (%s:%d - %s) added to unexisting channel %s\n", \
				get_client_addr(client->in), get_client_port(client->in), \
				client->nickname, name);
		}
		notif_channel(channel, client);
		client->send(client, client->serialize(JOIN_MESSAGE, name));
	}
	else
		client->send(client, \
			client->serialize(INFO_MESSAGE, \
				"The channel is invalid or empty"));
}
