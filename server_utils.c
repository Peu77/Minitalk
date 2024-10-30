/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebert <eebert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:57:47 by eebert            #+#    #+#             */
/*   Updated: 2024/10/30 18:24:31 by eebert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <stdlib.h>

void	reset_client_info(t_client_info *client_info)
{
	client_info->pid = 0;
	client_info->size = 0;
	if (client_info->str)
	{
		free(client_info->str);
		client_info->str = NULL;
	}
}

const t_receive_step_mapper	*get_receive_step_mapper(
		const t_receive_step_mapper *list,
		size_t size, t_receive_step step)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (list[i].step == step)
			return (&list[i]);
		i++;
	}
	return (NULL);
}
