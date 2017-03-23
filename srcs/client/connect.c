/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:27:57 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/21 19:27:58 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	connect_imbricate(char *data)
{
	char	**datas;
	int		port;

	datas = ft_strsplit(data, ':');
	port = 0;
	if (datas[0] != NULL && datas[1] != NULL)
	{
		port = ft_atoi(datas[1]);
		if (check_adress_v4(datas[0]) && (port > 0 && port <= MAX_PORT))
			connection(datas[0], port);
	}
	else
		printf("/connect: Syntax error (\"host:port\" or \"host\" \"port\")\n");
}

int		connect_cmd(char **split, t_client *client)
{
	int		port;

	if (client != NULL && client->connected == TRUE)
	{
		printf("/connect: You're already connected to server %s:%d\n", \
			client->remote_host, client->remote_port);
		return (TRUE);
	}
	port = 0;
	if (split[1] != NULL && split[2] != NULL)
	{
		port = ft_atoi(split[2]);
		if (check_adress_v4(split[1]) && (port > 0 && port <= MAX_PORT))
			connection(split[1], port);
		else
		{
			printf("/connect: Syntax error ");
			printf("(\"host:port\" or \"host\" \"port\")\n");
		}
	}
	else if (split[1] != NULL && split[2] == NULL)
		connect_imbricate(split[1]);
	else
		printf("/connect: Syntax error (\"host:port\" or \"host\" \"port\")\n");
	return (TRUE);
}
