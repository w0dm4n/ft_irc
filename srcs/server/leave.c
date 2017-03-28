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

void		leave_server(t_client *client)
{
	if (client != NULL && client->nickname != NULL \
		&& client->channel != NULL)
	{
		printf("User [%s] is leaving the channel [%s]\n", client->nickname, \
			client->channel->name);
		client->channel = NULL;
		//client->send(client, client->seri)
	}
}
