/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:58:04 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/21 18:58:12 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		handle(char *entry, t_client *client)
{
	char	**split;

	split = ft_strsplit(entry, ' ');
	if (split[0] != NULL)
	{
		if (!ft_strncmp(split[0], CONNECT_COMMAND, ft_strlen(CONNECT_COMMAND)))
			return (connect_cmd(split));
		if (!ft_strncmp(split[0], CLEAR_COMMAND, ft_strlen(CLEAR_COMMAND)))
			ft_putstr(CLEAR_SCREEN);
		if (!ft_strncmp(split[0], DISCONNECT_COMMAND, \
			ft_strlen(DISCONNECT_COMMAND)))
			return (disconnect(client));
	}
	return (TRUE);
}