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

void		*serialize_leave(char *data)
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
		client->send(client, client->serialize(LEAVE_MESSAGE, "\0"));
	else
		printf("/leave: You need to be in a channel to use leave\n");
}
