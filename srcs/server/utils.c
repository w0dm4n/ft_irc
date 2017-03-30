/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 00:28:40 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 00:29:01 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char			*int_to_hexastring(char c)
{
	char		*res;

	res = ft_itoabase_uint(c, "0123456789ABCDEF");
	if (ft_strlen(res) < 2)
		res = ft_strjoin("0", res);
	return (res);
}

char			hexastring_to_int(char *s)
{
	char xor;

	xor = ft_atoi_base(s, 16);
	ft_strdel(&s);
	return (xor);
}

char			*get_client_addr(struct sockaddr_in client)
{
	return (inet_ntoa(client.sin_addr));
}

int				get_client_port(struct sockaddr_in client)
{
	return (ntohs(client.sin_port));
}

t_client		*get_client_by_nickname(char *nickname)
{
	t_client	*clients;

	clients = g_clients;
	while (clients)
	{
		if (clients->nickname != NULL)
		{
			if (!ft_strcmp(ft_strtolower(clients->nickname), \
				ft_strtolower(nickname)))
				return (clients);
		}
		clients = clients->next;
	}
	return (NULL);
}
