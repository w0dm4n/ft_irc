/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encryption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 23:26:42 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/22 23:26:43 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static char		*xor_char(int i, char c)
{
	char *ret;

	ret = int_to_hexastring(c ^ ENCRYPTION_KEY[i % ft_strlen(ENCRYPTION_KEY)]);
	return (ret);
}

static char		*unxor_char(int i, char c)
{
	char *ret;

	ret = ft_strnew(1);
	ret[0] = c ^ ENCRYPTION_KEY[i % ft_strlen(ENCRYPTION_KEY)];
	return (ret);
}

char			*encrypt_message(char *msg)
{
	int		i;
	char	*crypted;

	i = 0;
	crypted = ft_strnew(0);
	while (msg[i])
	{
		crypted = ft_strjoin(crypted, xor_char(i, msg[i]));
		i++;
	}
	return (ft_strreverse(crypted));
}

char			*decrypt_message(char *crypted)
{
	int		i;
	int		n;
	char	*msg;

	crypted = ft_strreverse(crypted);
	i = 0;
	n = 0;
	msg = ft_strnew(0);
	while (crypted[n + 1])
	{
		msg = ft_strjoin(msg, unxor_char(i,\
			hexastring_to_int(ft_strsub(crypted, n, 2))));
		i++;
		n += 2;
	}
	return (msg);
}
