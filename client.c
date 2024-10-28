#include "ft_printf.h"
#include "libft.h"
#include "utils.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <wchar.h>

void	signal_handler(pid_t pid)
{
	static int		byte_i = 0;
	static size_t	bytes_send = 0;
	const int		bit = pid - 30;

	bytes_send |= ((pid_t)bit) << byte_i;
	byte_i++;
	if (byte_i == 32)
	{
		printf("send bytes: %zu\n", bytes_send);
		byte_i = 0;
	}
}

int	main(const int argc, char **argv)
{
	const int	pid = ft_atoi(argv[1]);
	const pid_t	my_pid = getpid();
	const char	*str = argv[2];

	(void)argc;
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	ft_printf("pid send to %d my_pid: %ul size_t \n", pid, my_pid);
	send_n_bytes_to_pid(pid, my_pid, sizeof(pid_t));
	send_n_bytes_to_pid(pid, ft_strlen(str), sizeof(size_t));
	while (*str)
	{
		send_n_bytes_to_pid(pid, *str, sizeof(char));
		str++;
	}
	send_n_bytes_to_pid(pid, 0, sizeof(char));
	for (int i = 0; i < 31; i++)
		pause();
	return (0);
}
