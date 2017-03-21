/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 03:07:49 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/19 03:07:50 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	handle(char *buffer, t_client *client)
{
	if (should_disconnect_client(buffer, client))
		return ;
	if (!ft_strcmp(buffer, WELCOME_BACK))
		welcome(client);
}