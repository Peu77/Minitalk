#include "utils.h"
#include <signal.h>
#include <sys/_types/_pid_t.h>
#include <sys/signal.h>
#include <unistd.h>
#include "ft_printf.h"
#include <stdio.h>
#include <stdbool.h>
#include "server.h"

static bool handle_receive_pid(t_client_info* client_info)
{
    printf("\nreceived pid: %d\n", client_info->pid);
    return true;
}

static bool handle_receive_size(t_client_info* client_info)
{
    printf("\nreceived size: %zu\n", client_info->size);
    client_info->str = malloc(client_info->size + 1);
    client_info->char_i = 0;
    if (!client_info->str)
    {
        ft_printf("failed to allocate memory\n");
        exit(1);
    }
    return true;
}

static bool handle_receive_data(t_client_info* client_info)
{
    if (client_info->char_i++ < client_info->size)
    {
        print_ascii_loading_animation(client_info->char_i, client_info->size);
        client_info->str[client_info->char_i] = client_info->current_char;
    }
    else
    {
        write(1, "\n", 1);
        write(1, client_info->str, client_info->char_i);
        write(1, "\n", 1);
        printf("sending response\n");
        send_n_bytes_to_pid(client_info->pid, client_info->char_i, sizeof(size_t), true);
        reset_client_info(client_info);
        return true;
    }
    client_info->current_char = 0;
    return false;
}

void signal_handler(int signal)
{
    static t_client_info client_info;
    const int bit = signal - 30;
    int i;
    const static t_receive_step_mapper receive_step_mapper[] = {
        {RECEIVE_PID, handle_receive_pid, sizeof(pid_t), &client_info.pid},
        {RECEIVE_SIZE, handle_receive_size, sizeof(size_t), &client_info.size},
        {RECEIVE_DATA, handle_receive_data, sizeof(char), &client_info.current_char}
    };

    i = 0;
    if(signal == SIGINT)
    {
        if (client_info.str)
            free(client_info.str);
        exit(0);
    }

    while (i != sizeof(receive_step_mapper) / sizeof(t_receive_step_mapper))
    {
        if (receive_step_mapper[i].step == client_info.step && read_n_bytes(
            receive_step_mapper[i].data, receive_step_mapper[i].data_size, bit, client_info.step != RECEIVE_DATA))
        {
            if (receive_step_mapper[i].fun(&client_info))
                client_info.step = (client_info.step + 1) % 3;
            break;
        }
        i++;
    }
}

int main(void)
{
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    signal(SIGINT, signal_handler);
    printf("pid: %d\n", getpid());
    while (pause());
    return (0);
}
