/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:52:48 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/28 17:52:49 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*serialize_leave(void)
{
	char	*to_send;

	if (!(to_send = ft_strnew(CLIENT_READ)))
		return (NULL);
	ft_strcat(to_send, LEAVE_MESSAGE);
	return (to_send);
}

void		leave_channel(t_client *client)
{
	char	*data;

	data = NULL;
	if (client != NULL && client->nickname != NULL && client->channel != NULL)
		client->send(client, client->serialize(LEAVE_MESSAGE, NULL));
	else
		printf("/leave: You need to be in a channel to use leave\n");
}

void		leaved(t_client *client)
{
	if (client != NULL && client->channel != NULL)
	{
		printf("You successfully leaved the channel %s\n", \
			client->channel->name);
		client->channel = NULL;
		print_prompt(client);
	}
}
