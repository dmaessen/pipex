/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:12:51 by dmaessen          #+#    #+#             */
/*   Updated: 2023/03/13 19:33:55 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_quotes(char *argv, int quote_s, int quote_d, int i)
{
	while (argv[i])
	{
		if (argv[i] == ' ' && quote_s == 0 && quote_d == 0)
			argv[i] = '"';
		else if (argv[i] == 39 && quote_s == 0 && quote_d == 0)
		{
			argv[i] = '"';
			quote_s = 1;
		}
		else if (argv[i] == 39 && quote_s == 1 && quote_d == 0)
		{
			argv[i] = '"';
			quote_s = 0;
		}
		else if (argv[i] == '"' && quote_d == 0)
			quote_d = 1;
		else if (argv[i] == '"' && quote_d == 1)
			quote_d = 0;
		else if (argv[i] == 39 && quote_d == 1)
			cmd_err(*ft_split(argv, '"'), 2);
		i++;
	}
	return (argv);
}

char	**split_command(char *argv)
{
	char	**command_str;
	int		i;
	int		quote_s;
	int		quote_d;

	i = 0;
	quote_s = 0;
	quote_d = 0;
	argv = ft_quotes(argv, quote_s, quote_d, i);
	command_str = ft_split(argv, '"');
	if (!command_str)
		return (NULL);
	return (command_str);
}
