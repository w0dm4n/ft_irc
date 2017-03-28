/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:09:18 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/27 19:09:20 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*serialize_who(void)
{
	char	*to_send;

	if (!(to_send = ft_strnew(CLIENT_READ)))
		return (NULL);
	ft_strcat(to_send, WHO_MESSAGE);
	ft_strcat(to_send, ESCAPE_CHAR);
	return (to_send);
}

void		who(t_client *client)
{
	if (client != NULL && client->connected == TRUE \
		&& client->nickname != NULL)
		client->send(client, client->serialize(WHO_MESSAGE, NULL));
	else
		printf("/who: You need to be connected with a nickname to use who\n");
}

void		print_data(char *nickname, char *channel)
{
	if (channel != NULL)
		printf("%s%s%s [%s%s%s]\n", KYEL, nickname, KNRM, \
			KRED, channel, KNRM);
	else
		printf("%s%s%s [no channel selected]\n", KYEL, nickname, KNRM);
}

void		who_from_server(char **data, t_client *client)
{
	int		i;
	char	**client_data;

	printf("\nWho is online ?\n _____________\n");
	i = 1;
	if (data != NULL)
	{
		while (data[i])
		{
			client_data = ft_strsplit(data[i], ESCAPE_DATA[0]);
			if (client_data[0])
				print_data(client_data[0], client_data[1]);
			i++;
		}
	}
	printf(" _____________\n");
	print_prompt(client);
}
