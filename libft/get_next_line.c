/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:42:13 by ohaggard          #+#    #+#             */
/*   Updated: 2022/11/07 18:56:40 by cojacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_file	buffer = {-1, {}, BUFFER_SIZE - 1, BUFFER_SIZE};
	char			*out;

	if (buffer.fd == 0 && buffer.cbuffer_size == 0)
	{
		buffer.cbuffer_size = BUFFER_SIZE;
		buffer.priv_last = BUFFER_SIZE - 1;
	}
	else if (buffer.cbuffer_size == 0)
		return (0);
	buffer.fd = fd;
	out = get_line(&buffer);
	return (out);
}
