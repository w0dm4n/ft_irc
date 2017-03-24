/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 03:40:31 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 03:40:32 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		informations(char **data, t_client *client)
{
	if (data[1])
	{
		printf("%sSERVER: %s%s\n", KCYN, data[1], KNRM);
		print_prompt(client);
	}
}

void		from_server(char *msg, t_client *client)
{
	char	**split;

	split = ft_strsplit(msg, ESCAPE_CHAR[0]);
	if (split[0] != NULL)
	{
		if (!ft_strcmp(split[0], NICK_MESSAGE))
			set_nickname(split, client);
		else if (!ft_strcmp(split[0], INFO_MESSAGE))
			informations(split, client);
		else if (!ft_strcmp(split[0], JOIN_MESSAGE))
			set_channel(split[1], client);
		else if (!ft_strcmp(split[0], CHANNEL_MESSAGE))
			channel_message(split[1], split[2], client);
	}
}