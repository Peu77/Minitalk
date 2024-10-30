/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:48:05 by eebert            #+#    #+#             */
/*   Updated: 2024/10/30 16:49:33 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils.h"
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

void	print_ascii_loading_animation(const size_t current, const size_t total)
{
	const size_t	bar_width = 50;
	const size_t	pos = (current * bar_width) / total;
	size_t			i;

	ft_printf("\r[");
	i = 0;
	while (i < bar_width)
	{
		if (i < pos)
			ft_printf("=");
		else if (i == pos)
			ft_printf(">");
		else
			ft_printf(" ");
		i++;
	}
	ft_printf("] %d%%", (current * 100) / total);
}

bool	read_n_bytes(const void *nb, const size_t bytes, const int bit,
		const bool print_progress)
{
	static size_t	bit_i = 0;
	uint8_t			*byte_ptr;

	byte_ptr = (uint8_t *)nb;
	byte_ptr[bit_i / 8] |= (bit << (bit_i % 8));
	bit_i++;
	if (print_progress)
		print_ascii_loading_animation(bit_i, bytes * 8);
	if (bit_i == bytes * 8)
	{
		bit_i = 0;
		return (true);
	}
	return (false);
}

void	send_n_bytes_to_pid(const pid_t pid, const unsigned long data,
		const int n, const bool print_progress)
{
	int			i;
	const int	bit = (data >> i) & 1;

	i = 0;
	while (i < n * 8)
	{
		kill(pid, 30 + bit);
		usleep(SEND_DELAY);
		i++;
		if (print_progress)
			print_ascii_loading_animation(i, n * 8);
	}
}
