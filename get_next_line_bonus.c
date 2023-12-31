/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:05:53 by ael-fagr          #+#    #+#             */
/*   Updated: 2023/12/28 01:34:42 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_get_line(char *buffer)
{
	size_t	i;
	char	*str;

	i = 0;
	if (buffer[i] == '\0' || !buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

static char	*ft_get_new_line(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (free(buffer), NULL);
	str = malloc(ft_strlen(buffer) - i);
	if (!str)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free (buffer);
	return (str);
}

static char	*ft_read_fun(int fd, char *buffer)
{
	char	*new_buff;
	int		_byte;

	new_buff = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!new_buff)
		return (free(buffer), NULL);
	_byte = 1;
	while (ft_strchr(buffer, '\n') == NULL && _byte > 0)
	{
		_byte = read(fd, new_buff, BUFFER_SIZE);
		if (_byte == -1)
			return (free(new_buff), free(buffer), NULL);
		new_buff[_byte] = '\0';
		buffer = ft_strjoin(buffer, new_buff);
		if (!buffer)
			return (NULL);
	}
	return (free(new_buff), buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[OPEN_MAX];

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read_fun(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_get_line(buffer[fd]);
	if (!line)
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	buffer[fd] = ft_get_new_line(buffer[fd]);
	return (line);
}