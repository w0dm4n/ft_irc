/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 18:21:19 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/28 18:21:20 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*serialize_leaved(void)
{
	char	*to_send;

	if (!(to_send = ft_strnew(CLIENT_READ)))
		return (NULL);
	ft_strcat(to_send, LEAVED_MESSAGE);
	return (to_send);
}

void		leave_server(t_client *client)
{
	if (client != NULL && client->nickname != NULL \
		&& client->channel != NULL)
	{
		printf("User [%s] is leaving the channel [%s]\n", client->nickname, \
			client->channel->name);
		client->channel = NULL;
		client->send(client, client->serialize(LEAVED_MESSAGE, NULL));
	}
}
