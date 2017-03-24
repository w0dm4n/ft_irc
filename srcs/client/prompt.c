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

void	print_channel(t_channel *channel)
{
	ft_putstr("] [");
	ft_putstr(KRED);
	ft_putstr(channel->name);
	ft_putstr(KNRM);
	ft_putstr("]: ");
}

void	print_nickname(t_client *client)
{
	ft_putstr(")] [");
	ft_putstr(KYEL);
	ft_putstr(client->nickname);
	ft_putstr(KNRM);
	if (client->channel == NULL)
		ft_putstr("]: ");
	else
		print_channel(client->channel);
}

void	print_host(t_client *client)
{
	ft_putstr(KGRN);
	ft_putstr(client->remote_host);
	ft_putstr(KNRM);
	ft_putstr(":");
	ft_putstr(KGRN);
	ft_putnbr(client->remote_port);
	ft_putstr(KNRM);
}

void	print_prompt(t_client *client)
{
	if (client != NULL && client->connected == TRUE)
	{
		ft_putstr(KNRM);
		ft_putstr("[FT_IRC (");
		print_host(client);
		if (client->nickname == NULL)
			ft_putstr(")]: ");
		else
			print_nickname(client);
	}
	else
		ft_putstr("[FT_IRC]: ");
}
