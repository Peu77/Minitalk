#include <sys/signal.h>
#include <unistd.h>
#include <signal.h>

void send_n_bytes_to_pid(pid_t pid, unsigned long data, int n)
{
    for(int i = 0; i < n * 8; i++)
    {
        const int bit = (data >> i) & 1;
        kill(pid, 30 + bit);
        usleep(100);
    }
}
