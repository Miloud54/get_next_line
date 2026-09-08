/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edidier <edidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:28:01 by edidier           #+#    #+#             */
/*   Updated: 2025/05/23 17:51:28 by edidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_extract_line(char *buffer)
{
	size_t	i;

	i = 0;
	if (!buffer || !buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	return (ft_substr(buffer, 0, i));
}

static char	*ft_save_rest(char *buffer)
{
	char	*rest;
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	rest = ft_substr(buffer, i + 1, ft_strlen(buffer) - i - 1);
	free(buffer);
	if (!rest)
		return (NULL);
	if (!*rest)
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}

static char	*ft_read_and_join(int fd, char *buf, char *storage)
{
	char	*tmp;
	ssize_t	bytes;

	bytes = 1;
	while (!ft_strchr(storage, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buf);
			free(storage);
			return (NULL);
		}
		buf[bytes] = '\0';
		tmp = storage;
		storage = ft_strjoin(tmp, buf);
		free(tmp);
		if (!storage)
		{
			free(buf);
			return (NULL);
		}
	}
	return (storage);
}

static char	*ft_read_file(int fd, char *storage)
{
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	storage = ft_read_and_join(fd, buf, storage);
	free(buf);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*new_storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	new_storage = ft_read_file(fd, storage);
	if (!new_storage)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	storage = new_storage;
	line = ft_extract_line(storage);
	storage = ft_save_rest(storage);
	return (line);
}
