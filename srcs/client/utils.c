/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 20:05:53 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/20 20:05:54 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*replace_newline(char *str)
{
	if (str[(ft_strlen(str) - 1)] == '\n')
		str[(ft_strlen(str) - 1)] = '\0';
	return (str);
}

int		split_size(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int		check_adress_v4(char *adress)
{
	char	**split;
	int		i;
	int		tmp;

	i = 0;
	split = ft_strsplit(adress, '.');
	while (split[i])
	{
		tmp = ft_atoi(split[i]);
		if (tmp > 255 || tmp < 0)
			return (FALSE);
		i++;
	}
	return ((split_size(split) == 4) ? TRUE : FALSE);
}

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
