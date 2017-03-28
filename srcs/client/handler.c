/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:58:04 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/21 18:58:12 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		handle_suite(char *entry, t_client *client, char **split)
{
	if (!ft_strncmp(split[0], EXIT_COMMAND, ft_strlen(EXIT_COMMAND)))
		exit(0);
	else if (!ft_strncmp(split[0], NICK_COMMAND, ft_strlen(NICK_COMMAND)))
		nickname(client, (split[1]) ? split[1] : NULL);
	else if (!ft_strncmp(split[0], JOIN_COMMAND, ft_strlen(JOIN_COMMAND)))
		join(client, (split[1]) ? split[1] : NULL);
	else if (!ft_strncmp(split[0], WHO_COMMAND, ft_strlen(WHO_COMMAND)))
		who(client);
	else if (!ft_strncmp(split[0], LEAVE_COMMAND, ft_strlen(LEAVE_COMMAND)))
		leave_channel(client);
	else
	{
		if (client != NULL && client->channel != NULL)
			return (talk_channel(entry, client, client->channel));
		else
			printf("Please connect to a channel or use a command.\n");
	}
	return (TRUE);
}

int		handle(char *entry, t_client *client)
{
	char	**split;

	split = ft_strsplit(entry, ' ');
	if (split[0] != NULL)
	{
		if (!ft_strncmp(split[0], CONNECT_COMMAND, \
			ft_strlen(CONNECT_COMMAND)))
			return (connect_cmd(split, client));
		else if (!ft_strncmp(split[0], CLEAR_COMMAND, \
			ft_strlen(CLEAR_COMMAND)))
			ft_putstr(CLEAR_SCREEN);
		else if (!ft_strncmp(split[0], DISCONNECT_COMMAND, \
			ft_strlen(DISCONNECT_COMMAND)))
			return (disconnect(client));
		else if (!ft_strncmp(split[0], HELP_COMMAND, \
			ft_strlen(HELP_COMMAND)))
			return (help());
		else
			return (handle_suite(entry, client, split));
	}
	return (TRUE);
}
