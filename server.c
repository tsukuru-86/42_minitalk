#include <signal.h>
#include <stdio.h>
#include <unistd.h>

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
        // write(1, &c, 1);
        printf("%c", c);
        fflush(stdout);
        g_char = 0;
        bit_count = 0;
    }
}

int main()
{
    printf("Current PID: %d\n", getpid()); //ft_printf
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    while(1)
    {
        pause();
    }

    return 0;
}