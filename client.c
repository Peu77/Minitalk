#include <signal.h>
#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"


void send_char_to_pid(int pid, char c)
{
    for(int i = 0; i < 8; i++)
    {
        unsigned long long bit = (c >> i) & 1;
        kill(pid, 30 + bit);
        usleep(500);
    }
}


int main(int argc, char** argv)
{
    (void) argc;
    int pid = ft_atoi(argv[1]);

    ft_printf("pid send to %d\n", pid);

    char* str = argv[2];

    while(*str)
    {
        send_char_to_pid(pid, *str);
        str++;
    }

}
