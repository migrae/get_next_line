/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraefen <mgraefen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:16:13 by mgraefen          #+#    #+#             */
/*   Updated: 2022/11/29 16:31:41 by mgraefen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_create_stash(int fd, char *stash)
{
	char	*buf;
	long	ret;

	ret = 1;
	buf = (char *) ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buf)
		return (free(stash), NULL);
	while (ret)
	{
		ret = read (fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (free(buf), free(stash), NULL);
		buf[ret] = '\0';
		if (!stash)
			stash = ft_strdup(buf);
		else
			stash = ft_strjoin(stash, buf);
		if (ft_strchr(stash, '\n') != 0)
			ret = 0;
		if (!stash)
			return (free(buf), NULL);
	}
	if (stash[0] == '\0')
		return (free(stash), free(buf), NULL);
	return (free(buf), stash);
}

char	*ft_create_line(char *stash)
{
	size_t	i;
	size_t	stop;
	char	*line;

	if (!stash)
		return (NULL);
	i = 0;
	stop = ft_len_to_line_end(stash, 1);
	line = (char *) ft_calloc(sizeof(char), ft_len_to_line_end(stash, 1) + 1);
	if (!line)
		return (free(stash), NULL);
	while (i < stop)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_create_new_stash(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	start;
	size_t	stash_len;

	if (!stash)
		return (NULL);
	i = 0;
	start = ft_len_to_line_end(stash, 1);
	stash_len = ft_len_to_line_end(stash, 0);
	new_stash = (char *) ft_calloc(sizeof(char), stash_len - start + 1);
	if (!new_stash)
		return (free(stash), NULL);
	while (stash[start + i])
	{
		new_stash[i] = stash[start + i];
		i++;
	}
	new_stash[i] = '\0';
	return (free(stash), new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_create_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_create_line(stash[fd]);
	if (!line)
		return (free(stash[fd]), NULL);
	stash[fd] = ft_create_new_stash(stash[fd]);
	if (!stash[fd])
		return (free(line), NULL);
	return (line);
}
