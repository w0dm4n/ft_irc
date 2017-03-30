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

char	*serialize_info(char *data)
{
	char	*to_send;

	if (!(to_send = ft_strnew(CLIENT_READ)))
		return (NULL);
	ft_strcat(to_send, INFO_MESSAGE);
	ft_strcat(to_send, ESCAPE_CHAR);
	ft_strcat(to_send, data);
	return (to_send);
}

char	*serializer(char *msg_type, char *data)
{
	if (!ft_strncmp(msg_type, NICK_MESSAGE, ft_strlen(NICK_MESSAGE)))
		return (serialize_nick(data));
	if (!ft_strncmp(msg_type, INFO_MESSAGE, ft_strlen(INFO_MESSAGE)))
		return (serialize_info(data));
	if (!ft_strncmp(msg_type, JOIN_MESSAGE, ft_strlen(JOIN_MESSAGE)))
		return (serialize_join(data));
	if (!ft_strncmp(msg_type, CHANNEL_MESSAGE, ft_strlen(CHANNEL_MESSAGE)))
		return (serialize_channel_msg(data));
	if (!ft_strncmp(msg_type, LEAVED_MESSAGE, ft_strlen(LEAVED_MESSAGE)))
		return (serialize_leaved());
	if (!ft_strncmp(msg_type, MP_MESSAGE, ft_strlen(MP_MESSAGE)))
		return (serialize_mp(data));
	return ("Unknown");
}
