/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:14:21 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/30 10:14:22 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char		*serialize_message(char *to_send, char *user)
{
	ft_strcat(to_send, MP_MESSAGE);
	ft_strcat(to_send, ESCAPE_CHAR);
	ft_strcat(to_send, ft_strtolower(user));
	ft_strcat(to_send, ESCAPE_DATA);
	return (to_send);
}

int			private_message(t_client *client, char **data, int i)
{
	char	*to_send;

	if (data[1] != NULL && data[2] != NULL && client != NULL)
	{
		if (!(to_send = ft_strnew(CLIENT_READ)))
			return (TRUE);
		to_send = serialize_message(to_send, data[1]);
		if (client != NULL && client->connected == TRUE)
		{
			while (data[++i])
			{
				if (ft_strlen(data[i]) > 0)
				{
					ft_strcat(to_send, replace_newline(data[i]));
					if (data[(i + 1)] != NULL)
						ft_strcat(to_send, " ");
				}
			}
		}
		client->send(client, to_send);
		return (FALSE);
	}
	else
		printf("/msg: Syntax error <user> <message>\n");
	return (TRUE);
}

void		received_pm(char **data, t_client *client)
{
	char	**split;

	split = NULL;
	if (data[1] != NULL)
	{
		split = ft_strsplit(data[1], ESCAPE_DATA[0]);
		if (split[0] && split[1])
		{
			if (ft_strcmp(ft_strtolower(split[0]), \
				ft_strtolower(client->nickname)))
				printf("\n");
			printf("[PM] [%s%s%s]: %s\n", KYEL, split[0], KNRM, split[1]);
			print_prompt(client);
		}
	}
}
