/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cojacque <cojacque@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:36:00 by ohaggard          #+#    #+#             */
/*   Updated: 2022/11/08 01:38:13 by cojacque         ###   ########.fr       */
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


// static char	*skip_spaces(char *s, char c)
// {
// 	if (*s == '\0')
// 		return (s);
// 	while (*s == c)
// 		s++;
// 	return (s);
// }

// static int	skip_and_add(char **s, char **str, char c)
// {
// 	int		size;
// 	char	*temp;

// 	size = 0;
// 	while ((*s)[size] != c && (*s)[size] != '\0')
// 		size++;
// 	*str = malloc(size + 1);
// 	if (!*str)
// 		return (0);
// 	temp = *str;
// 	while (**s != c && **s)
// 		*temp++ = *(*s)++;
// 	*temp = '\0';
// 	return (1);
// }

// static int	get_words_cnt(char *s, char c)
// {
// 	int	words;

// 	words = 0;
// 	while (1)
// 	{
// 		if (*s == c)
// 			s = skip_spaces(s, c);
// 		if (*s)
// 		{
// 			words++;
// 			s++;
// 			while (*s != c && *s)
// 				s++;
// 		}
// 		else
// 			return (words);
// 	}
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		words_cnt;
// 	char	*str1;
// 	char	**str2;
// 	char	**out;

// 	words_cnt = get_words_cnt((char *)s, c);
// 	out = malloc(sizeof(char *) * (words_cnt + 1));
// 	if (!out)
// 		return (0);
// 	str2 = out;
// 	str1 = (char *)s;
// 	while (1)
// 	{
// 		str1 = skip_spaces(str1, c);
// 		if (*str1)
// 		{
// 			if (!skip_and_add(&str1, str2, c))
// 				return (0);
// 			str2++;
// 		}
// 		else
// 			break ;
// 	}
// 	out[words_cnt] = NULL;
// 	return (out);
// }
