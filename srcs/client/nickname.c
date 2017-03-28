/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nickname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 01:24:33 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 01:24:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	set_nickname(char **data, t_client *client)
{
	if (data[1] != NULL)
	{
		client->nickname = data[1];
		printf("Your nickname is now %s\n", client->nickname);
		print_prompt(client);
	}
}

char	*serialize_nick(char *data)
{
	char	*to_send;

	if (!(to_send = ft_strnew(CLIENT_READ)))
		return (NULL);
	ft_strcat(to_send, NICK_MESSAGE);
	ft_strcat(to_send, ESCAPE_CHAR);
	ft_strcat(to_send, data);
	return (to_send);
}

void	nickname(t_client *client, char *nickname)
{
	if (client != NULL && client->connected == TRUE)
	{
		if (nickname != NULL && ft_strlen(replace_newline(nickname)) > 0)
			client->send(client, \
				client->serialize(NICK_MESSAGE, replace_newline(nickname)));
		else
			printf("/nick: Syntax error (/nick nickname)\n");
	}
	else
		printf("/nick: Please connect first !\n");
}
