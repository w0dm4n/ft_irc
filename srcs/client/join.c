/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 06:06:19 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 06:06:20 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		join(t_client *client, char *channel)
{
	if (client != NULL)
	{
		if (client->nickname != NULL && client->connected)
		{
			printf("Welcome to %s\n", channel);
		}
		else
		{
			printf("/join: You have to select a nickname before ");
			printf("joining a channel\n");
		}
	}
	else
		printf("/join: Please connect first !\n");
}