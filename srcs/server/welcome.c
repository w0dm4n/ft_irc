/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 00:46:09 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 00:46:11 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		should_disconnect_client(char *buffer, t_client *client)
{
	if (client->first == TRUE && ft_strcmp(buffer, WELCOME_BACK))
	{
		printf("%sOne client disconnected (%s:%d)%s\n", KRED,\
			get_client_addr(client->in), get_client_port(client->in), \
			KNRM);
		remove_client(&g_clients, client);
		close(client->fd);
		return (TRUE);
	}
	return (FALSE);
}

void	welcome(t_client *client)
{
	printf("Client %s:%d successfully authentified to the server !\n",
			get_client_addr(client->in), get_client_port(client->in));
	client->first = FALSE;
}
