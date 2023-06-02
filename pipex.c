/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:56:54 by dmaessen          #+#    #+#             */
/*   Updated: 2023/03/13 12:15:31 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(int in_file, int fd[], char *argv[], char *envp[])
{
	if (dup2(in_file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd[0]);
	close(in_file);
	split_arg(argv[2], envp);
}

void	child2(int out_file, int fd[], char *argv[], char *envp[])
{
	if (dup2(out_file, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd[1]);
	close(out_file);
	split_arg(argv[3], envp);
}

static void	execute_pipe(int in_file, int out_file, char *argv[], char *envp[])
{
	pid_t	process1;
	pid_t	process2;
	int		status;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	process1 = fork();
	if (process1 == -1)
		exit(EXIT_FAILURE);
	if (process1 == 0)
		child1(in_file, fd, argv, envp);
	process2 = fork();
	if (process2 == -1)
		exit(EXIT_FAILURE);
	if (process2 == 0)
		child2(out_file, fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(process1, &status, 0);
	waitpid(process2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int	main(int argc, char *argv[], char *envp[])
{
	int	in_file;
	int	out_file;

	if (argc != 5)
	{
		ft_putstr_fd("Error: invalid number of arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	in_file = open(argv[1], O_RDONLY);
	out_file = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (in_file < 0 || out_file < 0)
		no_perm_err(argc, argv);
	execute_pipe(in_file, out_file, argv, envp);
}
