/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 12:10:30 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/30 12:10:37 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		send_packet(t_client *client, char **split)
{
	if (client != NULL && client->connected == TRUE && split[1] != NULL)
		client->send(client, replace_newline(split[1]));
}
