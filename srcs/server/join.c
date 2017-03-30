/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 22:30:57 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 22:31:13 by frmarinh         ###   ########.fr       */
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

void		join_server(char *channel, t_client *client)
{
	if (channel != NULL && client != NULL)
		join_channel(ft_strtolower(channel), client, NULL);
	else
		client->send(client, \
			client->serialize(INFO_MESSAGE, \
				"An error occured while you was trying to join a channel"));
}
