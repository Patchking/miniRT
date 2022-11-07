/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:36:00 by ohaggard          #+#    #+#             */
/*   Updated: 2022/11/08 01:15:23 by cojacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	i = -1;
	if (!s)
		size = 0;
	else
		size = ft_strlen(s);
	if (size < start)
		len = 0;
	else if (size - start < len)
		len = size;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (++i < len)
		str[i] = s[start + i];
	str[i] = 0;
	return (str);
}

// char	*ft_substr(char const *s, unsigned int start,
// 				size_t len)
// {
// 	char	*out;
// 	size_t	size;

// 	size = ft_strlen((char *)s) + 1;
// 	if (size <= start + 1)
// 	{
// 		out = (char *)malloc(1);
// 		if (!out)
// 			return (0);
// 		*out = '\0';
// 		return (out);
// 	}
// 	s += start;
// 	len++;
// 	if (size > len)
// 		size = len;
// 	out = (char *)malloc(size);
// 	if (!out)
// 		return (0);
// 	ft_memcpy(out, s, size - 1);
// 	out[size - 1] = '\0';
// 	return (out);
// }
