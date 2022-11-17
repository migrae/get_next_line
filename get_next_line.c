/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraefen <mgraefen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:16:13 by mgraefen          #+#    #+#             */
/*   Updated: 2022/11/17 16:20:45 by mgraefen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	}
	free(buf);
	if (stash[0] == '\0')
		return (free(stash), NULL);
	return (stash);
}

char	*ft_create_line(char *stash)
{
	size_t	i;
	size_t	stop;
	char	*line;

	if (!stash)
		return (NULL);
	i = 0;
	stop = ft_len_to_line_end(stash, 1 + 1);
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
		return (free(stash), NULL);
	i = 0;
	start = ft_len_to_line_end(stash, 1 + 2);
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
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_create_stash(fd, stash);
	if (!stash)
		return (free(stash), NULL);
	line = ft_create_line(stash);
	if (!line)
		return (free(stash), NULL);
	stash = ft_create_new_stash(stash);
	if (!stash)
	{
		free(stash);
		free(line);
	}
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*test = (char *)1;

	fd = open("42_with_nl", O_RDWR);
	if (fd == -1)
	{
		printf("open() error");
		return (0);
	}
 	while (test)
	{
		test = get_next_line(fd);
		printf("'%s'", test); 
		char c = 0; read (fd, &c, 1);
		test = get_next_line(fd); 
		printf("'%s'", test); 
	}
	if (close(fd) == -1)
	{
		printf("close() error");
		return (0);
	}
	system("leaks a.out");
	return (0);
}
 */