/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:42:13 by ohaggard          #+#    #+#             */
/*   Updated: 2022/11/07 18:58:13 by cojacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_file
{
	int		fd;
	char	arr[BUFFER_SIZE];
	int		priv_last;
	int		cbuffer_size;
}	t_file;

int		gnl_strlen(char *str, int max);
char	*get_next_line(int fd);
int		join(char **s1, char *s2, int *size1, int max2);
char	*get_line(t_file *buffer);
int		getline_loop(t_file *buffer, char **out, int *out_size, int i);

#endif