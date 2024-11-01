/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:54:08 by eebert            #+#    #+#             */
/*   Updated: 2024/11/01 14:23:44 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <sys/types.h>

# define SEND_DELAY 60000

bool	read_n_bytes(const void *nb, const size_t bytes, const int bit,
			const bool print_progress);

void	send_n_bytes_to_pid(pid_t pid, unsigned long data, int n,
			const bool print_progress);

void	print_ascii_loading_animation(const size_t current, const size_t total);

int		signal_to_bit(int signal);

#endif