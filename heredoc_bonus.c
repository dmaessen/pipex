/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:58:35 by dmaessen          #+#    #+#             */
/*   Updated: 2023/03/15 17:34:34 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child1(t_pipexb pipex, int fd[])
{
	if (dup2(pipex.in_file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd[0]);
	close(pipex.in_file);
	split_args(pipex.argv[3], pipex.envp);
}

void	child2(t_pipexb pipex, int fd[])
{
	if (dup2(pipex.out_f, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd[1]);
	close(pipex.out_f);
	split_args(pipex.argv[4], pipex.envp);
}

static void	execute_pipe_std(t_pipexb pipex, int fd[])
{
	pid_t	process1;
	pid_t	process2;

	process1 = fork();
	if (process1 == -1)
		exit(EXIT_FAILURE);
	if (process1 == 0)
		child1(pipex, fd);
	process2 = fork();
	if (process2 == -1)
		exit(EXIT_FAILURE);
	if (process2 == 0)
		child2(pipex, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(process1, &pipex.status, 0);
	waitpid(process2, &pipex.status, 0);
	unlink("tmp_file");
	if (WIFEXITED(pipex.status))
		exit(WEXITSTATUS(pipex.status));
}

int	ft_heredoc(int argc, char *argv[], char *envp[])
{
	t_pipexb	pipex;
	int			fd[2];

	if (argc != 6)
	{
		ft_putstr_fd("Error: invalid number of arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	pipex.in_file = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pipex.out_f = open(argv[5], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex.in_file < 0 || pipex.out_f < 0)
		no_perm_err(argc, argv);
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	read_stdin(pipex);
	close(pipex.in_file);
	pipex.in_file = open("tmp_file", O_RDONLY);
	execute_pipe_std(pipex, fd);
	return (0);
}
