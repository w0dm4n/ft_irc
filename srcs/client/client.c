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

void		read_entry(char *entry, t_client *client)
{
	if ((read(STDIN_FILENO, entry, CLIENT_READ)) > 0)
	{
		if ((handle(entry, client) == TRUE))
			print_prompt(client);
		ft_bzero(entry, CLIENT_BUFFER);
	}
}

void		init_client(t_client *client)
{
	int			res;
	char		entry[CLIENT_BUFFER];

	res = 0;
	ft_bzero(entry, CLIENT_BUFFER);
	while (client->connected != FALSE)
	{
		FD_ZERO(&client->read_fds);
		FD_SET(client->fd, &client->read_fds);
		FD_SET(STDIN_FILENO, &client->read_fds);
		res = select(client->fd + 1, &client->read_fds, NULL, NULL, NULL);
		if (res == -1)
			print_error("An error occured with the select", -1);
		if (FD_ISSET(STDIN_FILENO, &client->read_fds))
			read_entry(entry, client);
		if (FD_ISSET(client->fd, &client->read_fds))
		{
			if ((read_server(client)) <= 0)
			{
				printf("You have been disconnected from the server\n");
				disconnect(client);
			}
		}
	}
}

void		connection(char *host, int port)
{
	t_client	*client;
	char		entry[CLIENT_BUFFER];

	if (!(client = get_client(host, port)))
		return ;
	if ((client->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		print_error("Can't create socket", 0);
		return ;
	}
	client->in.sin_addr.s_addr = inet_addr(host);
	client->in.sin_family = AF_INET;
	client->in.sin_port = htons(port);
	if ((connect(client->fd, (struct sockaddr*)&client->in, \
		sizeof(client->in))) < 0)
	{
		print_error("Can't connect to remote server", 0);
		return ;
	}
	client->connected = TRUE;
	ft_bzero(entry, CLIENT_BUFFER);
	print_prompt(client);
	init_client(client);
}

void		handle_connect(void)
{
	char		entry[CLIENT_BUFFER];

	print_prompt(NULL);
	ft_putstr("Please use /connect to authenticate !\n");
	print_prompt(NULL);
	ft_bzero(entry, CLIENT_BUFFER);
	while ((read(STDIN_FILENO, entry, CLIENT_READ)) > 0)
	{
		handle(entry, NULL);
		ft_bzero(entry, CLIENT_BUFFER);
		print_prompt(NULL);
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
		if ((host = get_host(argc, argv)) != NULL)
		{
			if ((port = get_port(argc, argv)) > 0)
				connection(host, port);
			else
			{
				printf("./client: Syntax error");
				printf(" (\"host:port\" or \"host\" \"port\")\n");
			}
		}
		else
		{
			printf("./client: Syntax error");
			printf(" (\"host:port\" or \"host\" \"port\")\n");
		}
	}
	else
		handle_connect();
}
