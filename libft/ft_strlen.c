/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:36:00 by ohaggard          #+#    #+#             */
/*   Updated: 2022/11/08 01:16:53 by cojacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = -1;
	while (s && s[++i])
		;
	return (i);
}

// int	ft_strlen(char *arr)
// {
// 	int	i;

// 	i = 0;
// 	while (*arr++ != 0)
// 		i++;
// 	return (i);
// }
