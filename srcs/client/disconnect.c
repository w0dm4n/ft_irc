/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 20:52:29 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/21 20:52:30 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		disconnect(t_client	*client)
{
	if (client)
	{
		client->connected = FALSE;
		close(client->fd);
		return (FALSE);
	}
	return (TRUE);
}
