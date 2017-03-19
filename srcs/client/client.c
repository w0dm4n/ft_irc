/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:58:54 by frmarinh          #+#    #+#             */
/*   Updated: 2017/03/16 15:00:07 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_client	*get_client(void)
{
	t_client	*client;
	if (!(client = (t_client*)malloc(sizeof(struct s_client))))
		return (NULL);

	client->fd = 0;
	client->next = NULL;
	client->prev = NULL;
	return (client);
}

void		handle_entry(char *entry)
{
	if (entry[0] == '/')
	{
		ft_putstr("Coucou");
	}
}

void		connection(char *host, int port)
{
	t_client	*client;
	char		entry[CLIENT_BUFFER];

	if (!(client = get_client()))
		return ;
	if ((client->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		print_error("Can't create socket", -1);
	client->in.sin_addr.s_addr = inet_addr(host);
	client->in.sin_family = AF_INET;
	client->in.sin_port = htons(port);
	if ((connect(client->fd, (struct sockaddr*)&client->in, sizeof(client->in))) < 0)
		print_error("Can't connect to remote server", -1);
	ft_bzero(entry, CLIENT_BUFFER);
	ft_putstr("[FT_IRC]: ");
	while ((read(0, entry, CLIENT_READ) > 0))
	{
		ft_putstr("[FT_IRC]: ");
		handle_entry(entry);
		ft_bzero(entry, CLIENT_BUFFER);
	}
}

int			main(int argc, char **argv)
{
	char	*host;
	int		port;

	host = NULL;
	port = 0;
	if (argc == 2 || argc == 3)
	{
		if ((host = get_host(argc, argv)) != NULL && (port = get_port(argc, argv)) > 0)
			connection(host, port);
		else
			printf("./client: Syntax error (\"host:port\" or \"host\" \"port\")\n");
	}
	else
		printf("./client: Syntax error (\"host:port\" or \"host\" \"port\")\n");
}
