/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:52:09 by dmaessen          #+#    #+#             */
/*   Updated: 2023/03/13 15:11:55 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

int		main(int argc, char *argv[], char *envp[]);
void	free_str(char **str);
void	cmd_err(char *arv, int error);
void	cmd_not_found(char **command);
void	no_perm_err(int argc, char *argv[]);
char	*split_arg(char *argv, char **envp);
char	**split_command(char *argv);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);
void	child1(int in_file, int fd[], char *argv[], char *envp[]);
void	child2(int out_file, int fd[], char *argv[], char *envp[]);

#endif
