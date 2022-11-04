/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaggard <ohaggard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:42:13 by ohaggard          #+#    #+#             */
/*   Updated: 2022/01/21 16:42:13 by ohaggard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	gnl_strlen(char *str, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (str[i] == '\n')
			return (i + 1);
		if (str[i] == '\0')
			return (i + 1);
		i++;
	}
	return (i);
}

int	join(char **s1, char *s2, int *size1, int max2)
{
	int		size2;
	int		i;
	int		e;
	char	*out;

	size2 = gnl_strlen(s2, max2);
	if (!*size1 && !size2)
		return (0);
	out = malloc(*size1 + gnl_strlen(s2, max2) + 1);
	if (!out)
		return (-1);
	i = -1;
	while (++i < *size1)
		out[i] = (*s1)[i];
	e = i - 1;
	while (++e < *size1 + size2)
		out[e] = s2[e - *size1];
	free(*s1);
	out[e] = '\0';
	*s1 = out;
	*size1 = e;
	return (e - i);
}

char	*get_line(t_file *buffer)
{
	char	*out;
	int		out_size;
	int		i;

	out = 0;
	out_size = 0;
	i = join(&out, buffer->arr + buffer->priv_last + 1,
			&out_size, buffer->cbuffer_size - buffer->priv_last - 1);
	if (i == -1)
		return (0);
	if (buffer->priv_last + i + 1 < BUFFER_SIZE)
	{
		printf("%d\n", i);
		buffer->priv_last += i;
		return (out);
	}
	while (1)
	{
		i = getline_loop(buffer, &out, &out_size, 0);
		if (i == 0)
			return (0);
		if (i == 1)
			return (out);
	}
}

int	getline_loop(t_file *buffer, char **out, int *out_size, int i)
{
	i = read(buffer->fd, buffer->arr, buffer->cbuffer_size);
	if (i == -1)
	{
		free(*out);
		return (0);
	}
	if (i < buffer->cbuffer_size)
	{
		buffer->cbuffer_size = i;
		buffer->arr[i] = '\0';
		if (i == 0)
			return (1);
	}
	i = join(out, buffer->arr, out_size, buffer->cbuffer_size);
	if (i == -1)
	{
		free(*out);
		return (0);
	}
	if ((*out)[*out_size - 1] == '\n')
	{
		buffer->priv_last = i - 1;
		return (1);
	}
	return (2);
}
