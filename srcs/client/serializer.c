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
	return ("Unknown");
}
