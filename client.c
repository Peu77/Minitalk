#include <signal.h>
#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"


void send_char_to_pid(const int pid,const char c)
{
    for(int i = 0; i < 8; i++)
    {
        const int bit = (c >> i) & 1;
        kill(pid, 30 + bit);
        usleep(500);
    }
}

void send_pid_to_pid(const pid_t pid)
{
    const pid_t me = getpid();

    for(int i = 0; i < 32; i++)
    {
        const int bit = (me >> i) & 1;
        kill(pid, 30 + bit);
        usleep(500);
    }
}


int main(const int argc, char** argv)
{
    (void) argc;
    const int pid = ft_atoi(argv[1]);
    const pid_t my_pid = getpid();

    ft_printf("pid send to %d my_pid: %ul\n", pid, my_pid);

    const char* str = argv[2];

    send_pid_to_pid(pid);

    while(*str)
    {
        send_char_to_pid(pid, *str);
        str++;
    }
    send_char_to_pid(pid, 0);

}
