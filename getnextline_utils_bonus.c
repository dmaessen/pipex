/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnext_line_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:06:47 by dmaessen          #+#    #+#             */
/*   Updated: 2023/03/09 16:08:17 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoin_gnl(char *memory, char *buf)
{
	size_t	i;
	size_t	len1;
	char	*join;

	if (!*memory && !*buf)
		return (free(memory), NULL);
	len1 = (ft_strlen(memory));
	join = ft_calloc((len1 + ft_strlen(buf) + 1), sizeof(char));
	if (!join)
		return (ft_free(&memory, NULL), NULL);
	i = 0;
	while (memory[i])
	{
		join[i] = memory[i];
		i++;
	}
	i = 0;
	while (buf[i])
	{
		join[len1 + i] = buf[i];
		i++;
	}
	join[len1 + ft_strlen(buf)] = '\0';
	return (free(memory), join);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	while (s[i] && s[i + 1] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (&str[i + 1]);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		sub = malloc(1 * sizeof(char));
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
