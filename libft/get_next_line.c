/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaggard <ohaggard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:42:13 by ohaggard          #+#    #+#             */
/*   Updated: 2022/01/21 16:42:13 by ohaggard         ###   ########.fr       */
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
