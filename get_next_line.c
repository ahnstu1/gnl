/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 05:15:39 by hahn              #+#    #+#             */
/*   Updated: 2022/03/16 08:56:52 by hahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_fd(char *remain, int fd)
{
	char	*buffer;
	int		read_return;

	read_return = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (1)
	{
		if (ft_strchr(remain, '\n') || !read_return)
			break ;
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_return] = '\0';
		remain = ft_strjoin(remain, buffer);
	}
	free(buffer);
	return (remain);
}

char	*prev_nl(char *remain)
{
	char	*output;
	int		len;
	int		idx;

	if (!*remain)
		return (NULL);
	len = ft_strlen(remain);
	if (ft_strchr(remain, '\n'))
		len -= (ft_strlen(ft_strchr(remain, '\n')) - 1);
	output = (char *)malloc(sizeof(char) * (len + 1));
	if (!output)
		return (NULL);
	idx = -1;
	while (++idx < len)
		output[idx] = remain[idx];
	output[idx] = '\0';
	return (output);
}

char	*next_nl(char *remain)
{
	char	*temp;
	char	*output;
	int		len;
	int		idx;

	temp = ft_strchr(remain, '\n');
	len = ft_strlen(temp);
	idx = -1;
	if (!temp || !temp[1])
	{
		free(remain);
		return (NULL);
	}
	output = (char *)malloc(sizeof(char) * len);
	if (!output)
		return (NULL);
	temp++;
	while (temp[++idx])
		output[idx] = temp[idx];
	output[idx] = '\0';
	free(remain);
	temp = NULL;
	return (output);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	remain = read_fd(remain, fd);
	if (!remain)
		return (NULL);
	line = prev_nl(remain);
	remain = next_nl(remain);
	return (line);
}
