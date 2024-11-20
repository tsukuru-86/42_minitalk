/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:32:57 by tsukuru           #+#    #+#             */
/*   Updated: 2024/11/20 18:21:05 by tsukuru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t g_char = 0;

void handle_signal(int sig)
{
    static int bit_count = 0;
    unsigned char c;

    g_char = g_char << 1;

    if(sig == SIGUSR1)
        g_char |= 1;
    bit_count++;
    if(bit_count == 8)
    {
        c = (unsigned char)g_char;
        write(1, &c, 1);
        fflush(stdout);
        g_char = 0;
        bit_count = 0;
    }
}

int main()
{
    ft_printf("Current PID: %d\n", getpid());
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    while(1)
    {
        pause();
    }

    return 0;
}