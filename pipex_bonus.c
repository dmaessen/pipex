/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:19:04 by dmaessen          #+#    #+#             */
/*   Updated: 2023/03/15 17:02:03 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	execute_pipe(t_pipexb pipex)
{
	pid_t	process;
	int		i;
	int		pos;

	i = 2;
	pos = 0;
	while (i < (pipex.argc - 1))
	{
		process = fork();
		if (process == -1)
			return (1);
		if (process == 0)
			which_child(pipex, i, pos);
		i++;
		pos++;
	}
	close_pipe(pipex.fd, pipex.argc);
	free_fd(pipex.fd, pipex.argc);
	close(pipex.in_file);
	close(pipex.out_f);
	waitpid(process, &pipex.status, 0);
	if (WIFEXITED(pipex.status))
		exit(WEXITSTATUS(pipex.status));
	return (0);
}

static int	**open_pipes(int argc)
{
	int		**fd;
	int		nb;
	int		i;

	nb = argc - 4;
	fd = (int **)malloc((nb) * sizeof(int *));
	i = 0;
	while (i < nb)
	{
		fd[i] = (int *)malloc(2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < nb)
	{
		if (pipe(fd[i]) < 0)
			return (NULL);
		i++;
	}
	return (fd);
}

void	close_pipe(int **fd, int argc)
{
	int	nb;
	int	i;

	nb = argc - 4;
	i = 0;
	while (i < nb)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	free_fd(int **fd, int argc)
{
	int	nb;
	int	i;

	nb = argc - 4;
	i = 0;
	while (i < nb)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipexb	pipex;

	if (argc < 5)
	{
		ft_putstr_fd("Error: invalid number of arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		ft_heredoc(argc, argv, envp);
	else
	{
		pipex.in_file = open(argv[1], O_RDONLY);
		pipex.out_f = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex.in_file < 0 || pipex.out_f < 0)
			no_perm_err(argc, argv);
		pipex.argc = argc;
		pipex.argv = argv;
		pipex.envp = envp;
		pipex.index = 0;
		pipex.fd = open_pipes(argc);
		if (pipex.fd == NULL)
			exit(EXIT_FAILURE);
		if (execute_pipe(pipex) == 1)
			exit(EXIT_FAILURE);
	}
}
