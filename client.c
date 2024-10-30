#include "ft_printf.h"
#include "libft.h"
#include "utils.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <wchar.h>

void signal_handler(int signal)
{
    static size_t bytes_send = 0;
    const int bit = signal - 30;

    if (read_n_bytes(&bytes_send, sizeof(size_t), bit, true))
    {
        printf("\nsend bytes: %zu\n", bytes_send);
        bytes_send = 0;
    }
}

int main(const int argc, char** argv)
{
    const int pid = ft_atoi(argv[1]);
    const pid_t my_pid = getpid();
    const char* str = argv[2];
    size_t i;

    (void)argc;
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    ft_printf("pid sending to %d my_pid: %ul size_t \n", pid, my_pid);
    ft_printf("sending my_pid\n");
    send_n_bytes_to_pid(pid, my_pid, sizeof(pid_t), true);
    ft_printf("\nsending size\n");
    send_n_bytes_to_pid(pid, ft_strlen(str), sizeof(size_t), true);
    printf("\nsending data\n");
    i = 0;
    while (str[i])
    {
        send_n_bytes_to_pid(pid, str[i], sizeof(char), false);
        i++;
        print_ascii_loading_animation(i, ft_strlen(str));
    }
    send_n_bytes_to_pid(pid, 0, sizeof(char), false);

    ft_printf("\nreceiving response\n");
    for (int i = 0; i < (int)sizeof(size_t) * 8 - 1; i++)
        pause();
    return (0);
}
