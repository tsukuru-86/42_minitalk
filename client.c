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
#include <errno.h>

static int g_transmission_complete = 0;

void signal_handler(int sig)
{
    (void)sig;
    g_transmission_complete = 1;
}

void send_message(pid_t server_pid, const char *str)
{
    int bit;
    char c;
    struct sigaction sa;
    
    // シグナルハンドラの設定
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        ft_printf("Error: Failed to setup signal handlers\n");
        exit(EXIT_FAILURE);
    }

    while (*str)
    {
        c = *str;
        bit = 7;
        while (bit >= 0)
        {
            g_transmission_complete = 0;
            
            // エラーチェック付きのシグナル送信
            if (kill(server_pid, (c & (1 << bit)) ? SIGUSR1 : SIGUSR2) == -1)
            {
                if (errno == ESRCH)
                    ft_printf("Error: Server process (PID: %d) not found\n", server_pid);
                else
                    ft_printf("Error: Failed to send signal (errno: %d)\n", errno);
                exit(EXIT_FAILURE);
            }

            // 制御された待機
            if (bit > 0)
            {
                for (int i = 0; i < 50 && !g_transmission_complete; i++)
                    usleep(100);
            }
            else
            {
                usleep(800); // 文字の最後のビットの後で長めの待機
            }
            bit--;
        }
        str++;
    }
}

int validate_server(pid_t pid)
{
    // プロセスの存在確認
    if (kill(pid, 0) == -1)
    {
        if (errno == ESRCH)
            ft_printf("Error: Server process (PID: %d) does not exist\n", pid);
        else if (errno == EPERM)
            ft_printf("Error: Permission denied to send signals to PID %d\n", pid);
        else
            ft_printf("Error: Unknown error while checking server PID\n");
        return (0);
    }
    return (1);
}

int main(int argc, char *argv[])
{
    pid_t server_pid;

    // 引数チェック
    if (argc != 3)
    {
        ft_printf("Usage: %s <server-pid> <string>\n", argv[0]);
        return (EXIT_FAILURE);
    }

    // PID変換とバリデーション
    server_pid = ft_atoi(argv[1]);
    if (server_pid <= 0)
    {
        ft_printf("Error: Invalid PID number\n");
        return (EXIT_FAILURE);
    }

    // サーバープロセスの確認
    if (!validate_server(server_pid))
        return (EXIT_FAILURE);

    // メッセージ送信
    send_message(server_pid, argv[2]);
    send_message(server_pid, "\n");

    // 最後のビットの送信を確実にするための待機
    usleep(1000);
    return (EXIT_SUCCESS);
}


// #include "minitalk.h"

// void	send_char(pid_t server_pid, char c)
// {
// 	int	bit;

// 	bit = 7;
// 	while (bit >= 0)
// 	{
// 		if (c & (1 << bit))
// 			kill(server_pid, SIGUSR1);
// 		else
// 			kill(server_pid, SIGUSR2);
// 		bit--;
// 		usleep(100);
// 	}
// }

// int	main(int argc, char *argv[])
// {
// 	pid_t	server_pid;
// 	char	*str;
// 	char	*msg;

// 	if (argc != 3)
// 	{
// 		msg = "Usage :%s <server-pid> <string>\n";
// 		write(2, msg, ft_strlen(msg));
// 		return (1);
// 	}
// 	server_pid = ft_atoi(argv[1]);
// 	str = argv[2];
// 	while (*str)
// 	{
// 		send_char(server_pid, *str);
// 		str++;
// 	}
// }
