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

// 単一のグローバル変数で両方の情報を管理
static volatile sig_atomic_t g_data = 0;
// ビット情報は上位24ビット、現在の文字は下位8ビットを使用

void handle_signal(int sig, siginfo_t *info, void *context)
{
    (void)context;
    (void)info;
    // static pid_t client_pid = 0;
    unsigned char c;
    int bit_count;

    // client_pid = info->si_pid;
    bit_count = (g_data >> 8) & 0xFF;  // ビットカウントを取得

    // 新しいビットを追加
    g_data = ((g_data & 0xFF) << 1);
    if (sig == SIGUSR1)
        g_data |= 1;
    bit_count++;

    if (bit_count == 8)
    {
        c = (unsigned char)(g_data & 0xFF);
        write(1, &c, 1);
        // if (client_pid)
        //     kill(client_pid, SIGUSR1);  // 確認シグナルを送信
        g_data = 0;  // リセット
    }
    else
    {
        // ビットカウントを保存
        g_data |= (bit_count << 8);
        // if (client_pid)
        //     kill(client_pid, SIGUSR2);
    }
}

int main(void)
{
    struct sigaction sa;

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
