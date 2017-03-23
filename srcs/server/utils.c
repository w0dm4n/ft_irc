/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 00:28:40 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/23 00:29:01 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*int_to_hexastring(char c)
{
	char		*res;

	res = ft_itoabase_uint(c, "0123456789ABCDEF");
	if (ft_strlen(res) < 2)
		res = ft_strjoin("0", res);
	return (res);
}

char	hexastring_to_int(char *s)
{
	char xor;

	xor = ft_atoi_base(s, 16);
	ft_strdel(&s);
	return (xor);
}
