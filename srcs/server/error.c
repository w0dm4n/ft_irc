/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:54:14 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/16 16:54:15 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static char		*get_error(void)
{
	if (errno == PERMISSION_DENIED)
		return ("Permission denied");
	if (errno == ALREADY_IN_USE)
		return ("Port already in use");
	return ("Unknown error");
}

void			print_error(char *msg, int exit_code)
{
	printf("./serveur: %s: %s\n", msg, get_error());
	if (exit_code != 0)
		exit(exit_code);
}
