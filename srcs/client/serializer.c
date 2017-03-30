/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serializer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 02:21:31 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 02:21:32 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*serializer(char *msg_type, char *data)
{
	if (!ft_strncmp(msg_type, NICK_MESSAGE, ft_strlen(NICK_MESSAGE)))
		return (serialize_nick(data));
	if (!ft_strncmp(msg_type, JOIN_MESSAGE, ft_strlen(JOIN_MESSAGE)))
		return (serialize_join(data));
	if (!ft_strncmp(msg_type, CHANNEL_MESSAGE, ft_strlen(CHANNEL_MESSAGE)))
		return (serialize_channel_msg(data));
	if (!ft_strncmp(msg_type, WHO_MESSAGE, ft_strlen(WHO_MESSAGE)))
		return (serialize_who());
	if (!ft_strncmp(msg_type, LEAVE_MESSAGE, ft_strlen(LEAVE_MESSAGE)))
		return (serialize_leave());
	return ("Unknown");
}
