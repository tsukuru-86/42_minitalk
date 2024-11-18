#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal(int sig)
{
    (void)sig;
    printf("I got your information.\n");
}

int main()
{
    printf("Current PID: %d\n", getpid()); //ft_printf
    signal(SIGUSR1, handle_signal);
    while(1)
    {
        printf("Waitng...\n"); //ft_printf
        sleep(3);
    }

    return 0;
}