/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:33:10 by tsukuru           #+#    #+#             */
/*   Updated: 2024/11/22 07:12:14 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"
#include <errno.h>

static int	g_transmission_complete = 0;

void	signal_handler(int sig)
{
	(void)sig;
	g_transmission_complete = 1;
}

static void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error: Failed to setup signal handlers\n");
		exit(1);
	}
}

void	signal_roop(pid_t server_pid, int bit, char c)
{
	g_transmission_complete = 0;
	if (kill(server_pid, (c & (1 << bit)) ? SIGUSR1 : SIGUSR2) == -1)
	{
		ft_printf("Error.\n");
		exit(1);
	}
	usleep(100);
}

void	send_message(pid_t server_pid, char *str)
{
	int		bit;
	char	c;

	setup_signal_handlers();
	while (*str)
	{
		c = *str;
		bit = 7;
		while (bit >= 0)
		{
			signal_roop(server_pid, bit, c);
			bit--;
		}
		str++;
	}
}

int	validate_server(pid_t pid)
{
	if (kill(pid, 0) == -1)
	{
		ft_printf("Eroor: Unable to Communicate with PID %d: %s\n", pid, strerror(errno));
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server-pid> <string>\n", argv[0]);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf("Error: Invalid PID number\n");
		return (1);
	}
	if (!validate_server(server_pid))
		return (1);
	send_message(server_pid, argv[2]);
	send_message(server_pid, "\n");
	usleep(1000);
	return (0);
}
