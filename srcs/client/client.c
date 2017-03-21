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

void			send_data(t_client *client, char *msg)
{
	if (client->fd)
		write(client->fd, msg, ft_strlen(msg));
}

t_client	*get_client(void)
{
	t_client	*client;
	if (!(client = (t_client*)malloc(sizeof(struct s_client))))
		return (NULL);

	client->fd = 0;
	client->next = NULL;
	client->prev = NULL;
	client->first = TRUE;
	client->send = send_data;
	return (client);
}

void		handle_entry(char *entry, t_client *client)
{
	if (entry[0] == '/')
	{
		client->send(client, "Coucou\0");
		ft_putstr("Coucou\n");
	}
}

void		check_welcome(char *message, t_client *client)
{
	if (ft_strcmp(message, WELCOME_MESSAGE))
	{
		printf("./client: Invalid message received from the server\n");
		exit(0);
	}
	else
	{
		printf("You're successfully connected to the server !\n");
		ft_putstr("[FT_IRC]: ");
		write(client->fd, WELCOME_BACK, ft_strlen(WELCOME_BACK));
	}
}

int			read_server(t_client *client)
{
	int 		res;
	char		buffer[CLIENT_BUFFER];

	res = recv(client->fd, buffer, CLIENT_READ, 0);
	if (res > 0)
	{
		if (client->first == TRUE)
		{
			check_welcome(buffer, client);	
			client->first = FALSE;
		}
	}
	return (res);
}

void		init_client(t_client *client)
{
	int 		res;
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
		{
			if ((read(STDIN_FILENO, entry, CLIENT_READ)) > 0)
			{
				handle_entry(entry, client);
				ft_bzero(entry, CLIENT_BUFFER);
				ft_putstr("[FT_IRC]: ");
			}
		}
		if (FD_ISSET(client->fd, &client->read_fds))
		{
			if ((read_server(client)) <= 0)
			{
				printf("You have been disconnected from the server\n");
				client->connected = FALSE;
			}
		}
	}
}

void		connection(char *host, int port)
{
	t_client	*client;
	char		entry[CLIENT_BUFFER];
	static		int first;

	first = TRUE;
	if (!(client = get_client()))
		return ;
	if ((client->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		print_error("Can't create socket", -1);
	client->in.sin_addr.s_addr = inet_addr(host);
	client->in.sin_family = AF_INET;
	client->in.sin_port = htons(port);
	if ((connect(client->fd, (struct sockaddr*)&client->in, \
		sizeof(client->in))) < 0)
		print_error("Can't connect to remote server", -1);
	client->connected = TRUE;
	ft_bzero(entry, CLIENT_BUFFER);
	ft_putstr("[FT_IRC]: ");
	init_client(client);
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
