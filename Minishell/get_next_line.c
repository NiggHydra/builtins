/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 07:37:00 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/07/23 16:55:37 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*transfer_in_buffer(int fd)
{
	char	*buf;
	int		bit_read;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	bit_read = (int)read(fd, buf, BUFFER_SIZE);
	if (bit_read <= 0)
	{
		free(buf);
		return (NULL);
	}
	buf[bit_read] = '\0';
	return (buf);
}

int	browse_line(char **line_reserve)
{
	int		i;

	i = 0;
	while (i[*line_reserve] != '\n' && i[*line_reserve] != '\0')
		i++;
	return (i);
}

char	*verify_line(char **line_reserve)
{
	char	*line_found;
	char	*backup;
	int		i;
	int		here;

	i = browse_line(line_reserve);
	if (i[*line_reserve] == '\n')
	{
		here = i + 1;
		line_found = ft_substr(*line_reserve, 0, here);
		backup = ft_substr(*line_reserve, here, ft_strlen(*line_reserve) - i);
		free(*line_reserve);
		*line_reserve = backup;
		return (line_found);
	}
	return (NULL);
}

char	*transfer_in_reserve(char **reserve, int fd)
{
	char	*backup_reserve;
	char	*line;
	char	*s;

	line = verify_line(reserve);
	if (line)
		return (line);
	s = transfer_in_buffer(fd);
	if (!s)
	{
		line = ft_strdup(*reserve);
		free(*reserve);
		*reserve = NULL;
		if (*line)
			return (line);
		free (line);
		return (NULL);
	}
	backup_reserve = ft_strjoin(*reserve, s);
	*reserve = backup_reserve;
	free (s);
	return (get_next_line(fd));
}

char	*get_next_line(int fd)
{
	static char	*reserve;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(reserve);
		reserve = NULL;
		return (NULL);
	}
	if (!reserve)
		reserve = ft_strdup("");
	return (transfer_in_reserve(&reserve, fd));
}
