/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:32:57 by tsukuru           #+#    #+#             */
/*   Updated: 2024/11/22 07:12:16 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_data = 0;

void	receive_bit(int sig, pid_t client_pid)
{
	int	bit_count;

	(void)client_pid;
	bit_count = (g_data >> 8) & 0xFF;
	g_data = ((g_data & 0xFF) << 1);
	if (sig == SIGUSR1)
		g_data |= 1;
	bit_count++;
	g_data = (g_data & 0xFF) | (bit_count << 8);
}

void	process_data(pid_t client_pid)
{
	unsigned char	c;
	int				bit_count;

	bit_count = (g_data >> 8) & 0xFF;
	if (bit_count == 8)
	{
		c = (unsigned char)(g_data & 0xFF);
		write(1, &c, 1);
		if (client_pid)
			kill(client_pid, SIGUSR1);
		g_data = 0;
	}
	else
	{
		if (client_pid)
			kill(client_pid, SIGUSR2);
	}
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static pid_t	client_pid;

	client_pid = 0;
	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (client_pid != info->si_pid)
		return ;
	receive_bit(sig, client_pid);
	process_data(client_pid);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Error setting up SIGUSR1\n");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up SIGUSR2\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}