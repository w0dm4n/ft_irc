/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 20:06:36 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/21 20:06:37 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	print_prompt(t_client *client)
{
	if (client != NULL && client->connected == TRUE)
	{
		ft_putstr("[FT_IRC (");
		ft_putstr(client->remote_host);
		ft_putstr(":");
		ft_putnbr(client->remote_port);
		ft_putstr(")]: ");
	}
	else
		ft_putstr("[FT_IRC]: ");
}