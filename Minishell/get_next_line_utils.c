/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:41:52 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/09/17 16:26:31 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

//char	*ft_strjoin(char const *s1, char const *s2)
//{
//	char	*mem;
//	size_t	i;
//	size_t	j;
//	size_t	len;

//	len = ft_strlen(s1) + ft_strlen(s2);
//	mem = malloc(sizeof(char) * (len + 1));
//	if (!mem)
//		return (NULL);
//	i = 0;
//	while (s1[i])
//	{
//		mem[i] = s1[i];
//		i++;
//	}
//	j = 0;
//	while (s2[j])
//	{
//		mem[i + j] = s2[j];
//		j++;
//	}
//	mem[i + j] = '\0';
//	free((char *)s1);
//	return (mem);
//}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == NULL && src == NULL)
		return (dest);
	while (i < n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char		*ptr;
	size_t		len;

	len = ft_strlen(s) + 1;
	ptr = (char *)malloc(sizeof(char) * (len));
	if (!ptr)
		return (NULL);
	if (ptr)
		ft_memcpy(ptr, s, len);
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*mem;
	unsigned int		i;
	unsigned int		length;

	if (s == NULL || start >= ft_strlen(s))
		return (ft_strdup(""));
	length = ft_strlen(s + start);
	if (length < len)
		len = length;
	mem = malloc(sizeof(char) * (len + 1));
	if (!mem)
		return ((char *)0);
	i = start;
	while (i < len + start)
	{
		*(mem + i - start) = *(s + i);
		i ++;
	}
	*(mem + i - start) = '\0';
	return (mem);
}
