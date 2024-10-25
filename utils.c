#include <sys/signal.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void send_n_bytes_to_pid(pid_t pid, unsigned long data, int n)
{
    int i = 0;

    while (i < n * 8)
    {
        const int bit = (data >> i) & 1;
        kill(pid, 30 + bit);
        usleep(100);

        i++;
    }
}
