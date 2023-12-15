/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:01:23 by ael-fagr          #+#    #+#             */
/*   Updated: 2023/12/15 05:47:00 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *buffer)
{
	int		i;
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

char	*ft_get_new_line(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free (buffer);
		return (NULL);
	}
	str = (char *)malloc(ft_strlen(buffer) - i);
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free (buffer);
	return (str);
}

char	*ft_read_fun(int fd, char *buffer)
{
	char	*new_buff;
	int		_byte;

	new_buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!new_buff)
		return (NULL);
	_byte = 1;
	while (ft_strchr(buffer, '\n') == 0 && _byte != 0)
	{
		_byte = read(fd, new_buff, BUFFER_SIZE);
		if (_byte == -1)
		{
			free(new_buff);
			return (NULL);
		}
		new_buff[_byte] = '\0';
		buffer = ft_strjoin(buffer, new_buff);
	}
	free(new_buff);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = 0;
	buffer = ft_read_fun(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_get_new_line(buffer);
	return (line);
}
