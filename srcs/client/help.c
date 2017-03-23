/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 20:01:45 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/22 20:01:52 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int			help(void)
{
	printf("List of commands for [FT_IRC]: \n");
	printf("- /connect: host:port for remote connection to a server\n");
	printf("- /disconnect: for disconnecting from remote server\n");
	printf("- /clear: clear the term from all entry\n");
	printf("- /help: Print all available commands\n");
	printf("- /nick: Set a nickname\n");
	printf("- /join: Join a channel\n");
	printf("- /exit: Close the program\n");
	return (TRUE);
}
