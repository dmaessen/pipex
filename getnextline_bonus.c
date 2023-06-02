/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:04:24 by dmaessen          #+#    #+#             */
/*   Updated: 2023/03/10 15:35:35 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char **memory, char *line)
{
	free(*memory);
	*memory = NULL;
	free(line);
}

static char	*current_line(char *memory)
{
	size_t	i;
	char	*line;

	i = 0;
	while (memory[i] != '\0' && memory[i] != '\n')
		i++;
	if (memory[i] == '\n')
		i++;
	line = ft_substr(memory, 0, i);
	if (!line)
		return (free(line), NULL);
	return (line);
}

static char	*sub_mem(char *memory)
{
	size_t	i;
	size_t	len;
	char	*sub;

	i = 0;
	len = ft_strlen(memory);
	while (memory[i] != '\0' && memory[i] != '\n')
		i++;
	if (memory[i] == '\n')
		i++;
	if (!memory[i])
		return (free(memory), NULL);
	sub = ft_substr(memory, i, len - i);
	if (!sub)
		return (ft_free(&memory, NULL), NULL);
	free(memory);
	return (sub);
}

static char	*reading(int fd, char *memory)
{
	int		nbyte;
	char	*buf;

	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (free(memory), NULL);
	nbyte = 1;
	while (nbyte != 0 && !ft_strchr(memory, '\n'))
	{
		nbyte = read(fd, buf, BUFFER_SIZE);
		if (nbyte < 0)
			return (ft_free(&memory, buf), NULL);
		buf[nbyte] = '\0';
		memory = ft_strjoin(memory, buf);
		if (!memory)
			return (ft_free(&memory, buf), NULL);
	}
	free (buf);
	return (memory);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	if (!memory)
	{
		memory = ft_calloc(1, 1);
		if (!memory)
			return (NULL);
	}
	memory = reading(fd, memory);
	if (!memory)
		return (free(memory), NULL);
	newline = current_line(memory);
	if (!newline)
		return (ft_free(&memory, NULL), NULL);
	memory = sub_mem(memory);
	return (newline);
}
