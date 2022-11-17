/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraefen <mgraefen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:27:27 by mgraefen          #+#    #+#             */
/*   Updated: 2022/11/17 16:06:37 by mgraefen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_len_to_line_end(char *str, int line_break)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] && (str[len] != '\n' || !line_break))
		len++;
	if (str[len] == '\n')
		len++;
	return (len);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if (size && count > SIZE_MAX / size)
		return (0);
	str = (void *) malloc(size * count);
	if (!str)
		return (NULL);
	while (i < size * count)
			str[i++] = '\0';
	return ((void *) str);
}

char	*ft_strdup(char *s1)
{
	char	*copy;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_len_to_line_end(s1, 0) + 1;
	copy = (char *) ft_calloc(sizeof(char), len);
	if (!copy)
		return (free(s1), NULL);
	while (i < (len - 1) && s1[i] && len > 1)
	{
		copy[i] = s1[i];
		i++;
	}
	if (len != 0)
		copy[i] = '\0';
	while (s1[i] != '\0')
		i++;
	return ((char *)copy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*sub;
	size_t	i;
	size_t	i2;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (0);
	i = 0;
	i2 = 0;
	s1_len = ft_len_to_line_end(s1, 0);
	s2_len = ft_len_to_line_end(s2, 0);
	sub = (char *)ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!sub)
		return (free(s1), free(s2), NULL);
	while (i < s1_len)
	{
		sub[i] = s1[i];
		i++;
	}
	while (i2 < s2_len)
		sub[i++] = s2[i2++];
	sub[i] = '\0';
	return (free(s1), sub);
}

char	*ft_strchr(const char *s, int c)
{
	if (c < 0)
		return ((char *)s);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
