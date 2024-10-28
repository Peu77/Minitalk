#include "utils.h"
#include <signal.h>
#include <sys/_types/_pid_t.h>
#include <sys/signal.h>
#include <unistd.h>
#include "ft_printf.h"
#include <stdio.h>
#include <stdbool.h>

bool read_n_bytes(void* nb, size_t bytes, int bit)
{
	static size_t bit_i = 0;
	uint8_t *byte_ptr = (uint8_t *)nb;

	byte_ptr[bit_i / 8] |= (bit << (bit_i % 8));
	bit_i++;
	if (bit_i == bytes * 8)
	{
		bit_i = 0;
		return true;
	}
	return false;
}

void	signal_handler(pid_t pid)
{
	static char		c;
	static pid_t	client_pid;
	static size_t	char_i = 0;
	static size_t	size = 0;
	static t_receive_step step = RECEIVE_PID;
	const int		bit = pid - 30;

	if (step == RECEIVE_PID)
	{
		if(read_n_bytes(&client_pid, sizeof(pid_t), bit))
		{
			step = RECEIVE_SIZE;
			ft_printf("client_id: %d\n", client_pid);
		}
		return;
	}

	if(step == RECEIVE_SIZE)
	{
		if(read_n_bytes(&size, sizeof(size_t), bit))
		{
			step = RECEIVE_DATA;
			printf("size: %zu\n", size);
		}
		return;
	}

	if(read_n_bytes(&c, sizeof(char), bit))
	{
		write(1, &c, 1);
		if (c == 0)
		{
			send_n_bytes_to_pid(client_pid, char_i, sizeof(size_t));
			write(1, "\n", 1);
			client_pid = 0;
		}
		char_i++;
		c = 0;
	}
}

int	main(void)
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	printf("pid: %d\n", getpid());
	while (pause())
		;
	return (0);
}
