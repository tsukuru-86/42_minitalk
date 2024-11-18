#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void send_char(pid_t server_pid, char c)
{
    int digit = 7;
	while (digit >= 0)
	{
		if (c & (1 << digit))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		digit--;
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
        fprintf(stderr, "Usage :%s <server-pid> <string>\n", argv[0]); //fprintfを自作の必要あり
        return 1;
    }

    server_pid = atoi(argv[1]); //ft_atoiに変える必要あり
    str = argv[2];

    while(*str)
    {
        send_char(server_pid, *str);
        str++;
    }
}