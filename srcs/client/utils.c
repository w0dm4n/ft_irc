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
	char **split;
	int	i;
	int	tmp;

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
