/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 03:07:49 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/19 03:07:50 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		handle_esc(char **split, t_client *client, char *data)
{
	if (!ft_strcmp(split[0], NICK_MESSAGE))
		nickname_server(split[1], client);
	else if (!ft_strcmp(split[0], JOIN_MESSAGE))
		join_server(split[1], client);
	else if (!ft_strcmp(split[0], CHANNEL_MESSAGE))
		talk_channel_server(split, client, client->channel);
	else
		printf("%sMessage not handled: %s from %s:%d%s\n", \
			KYEL, data, get_client_addr(client->in), \
			get_client_port(client->in), KNRM);
	return (TRUE);
}

int		handle(char *buffer, t_client *client)
{
	char	**split;

	if (client != NULL)
	{
		split = ft_strsplit(buffer, ESCAPE_CHAR[0]);
		if (should_disconnect_client(buffer, client))
			return (FALSE);
		else if (!ft_strcmp(buffer, WELCOME_BACK))
			welcome(client);
		else if (split[0] != NULL)
			return (handle_esc(split, client, buffer));
	}
	return (TRUE);
}
