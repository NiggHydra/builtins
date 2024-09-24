/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 07:39:28 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/09/17 16:25:32 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

char		*verify_line(char **line_reserve);
int			browse_line(char **line_reserve);
char		*transfer_in_reserve(char **reserve, int fd);
char		*transfer_read_in_buffer(int fd);
char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif
