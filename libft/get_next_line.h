/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:42:13 by ohaggard          #+#    #+#             */
/*   Updated: 2022/11/08 01:11:14 by cojacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include   <unistd.h>
# include   <stdlib.h>
# include   <limits.h>

# include   "libft.h"

void	ft_fill_line(char **rmd, char **line, int size);
void	ft_handle_remainder(char **rmd, char **line);
int		ft_read(int fd, char **rmd, char **buf, char **line);
char	*get_next_line(int fd);

#endif
