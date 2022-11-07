/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:36:00 by ohaggard          #+#    #+#             */
/*   Updated: 2022/11/08 01:52:41 by cojacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_word_count(char const *s, char c)
{
	unsigned int	i;
	unsigned int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i])
				i++;
			i--;
		}
		i++;
	}
	return (words);
}

static void	set_index(char const *s, unsigned int *st, unsigned int *en, char c)
{
	while (s[*st] && s[*st] == c)
		(*st)++;
	*en = *st;
	while (s[*en] && s[*en] != c)
		(*en)++;
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	end;
	unsigned int	start;
	unsigned int	words;
	char			**array;

	i = 0;
	start = 0;
	if (!s)
		return (NULL);
	words = get_word_count(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	while (i < words)
	{
		set_index(s, &start, &end, c);
		array[i] = ft_substr(s, start, end - start);
		start = end;
		i++;
	}
	array[i] = NULL;
	return (array);
}
