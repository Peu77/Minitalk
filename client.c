/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:06:11 by eebert            #+#    #+#             */
/*   Updated: 2024/11/01 15:42:44 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "utils.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <wchar.h>

static void	signal_handler(int signal)
{
	static size_t	bytes_send = 0;
	const int		bit = signal_to_bit(signal);

	if (read_n_bytes(&bytes_send, sizeof(size_t), bit, true))
	{
		printf("\nsend bytes: %zu\n", bytes_send);
		bytes_send = 0;
	}
}

static void	pause_n_times(size_t n)
{
	while (n--)
		pause();
}

static void	parse_args(const int argc, char **argv, int *pid, char **str)
{
	if (argc != 3)
	{
		ft_printf("usage: %s <pid> <string>\n", argv[0]);
		exit(1);
	}
	*pid = ft_atoi(argv[1]);
	*str = argv[2];
	if (*pid <= 0)
	{
		ft_printf("Invalid pid\n");
		exit(1);
	}
	if (**str == '\0')
	{
		ft_printf("Invalid string\n");
		exit(1);
	}
}

int	main(const int argc, char **argv)
{
	const pid_t	my_pid = getpid();
	int			pid;
	char		*str;
	size_t		i;

	parse_args(argc, argv, &pid, &str);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
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
	ft_printf("\nreceiving response\n");
	return (pause_n_times(sizeof(size_t) * 8 - 1), 0);
}
