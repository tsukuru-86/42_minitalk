/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:33:10 by tsukuru           #+#    #+#             */
/*   Updated: 2024/11/20 18:21:42 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void send_char(pid_t server_pid, char c)
{
    int bit = 7;
	while (bit >= 0)
	{
		if (c & (1 << bit))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		bit--;
		usleep(100);
	}
    // int bit;

    // bit = 0;
    // while(bit < 8)
    // {
    //     if(c & (1 << bit))
    //         kill(server_pid, SIGUSR1);
    //     else
    //         kill(server_pid, SIGUSR2);

    //     bit++;
    //     usleep(100);
    // }
}

int main(int argc, char *argv[])
{
    pid_t server_pid;
    char *str;

    if(argc != 3)
    {
        const char *msg = "Usage :%s <server-pid> <string>\n";
        write(2, msg, ft_strlen(msg));
        return 1;
    }

    server_pid = ft_atoi(argv[1]);
    str = argv[2];

    while(*str)
    {
        send_char(server_pid, *str);
        str++;
    }
}