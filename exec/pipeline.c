/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:36:14 by isastre-          #+#    #+#             */
/*   Updated: 2025/09/26 16:52:02 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @param n the number of cmds in the pipeline
 */
void	ft_create_pipes(t_minishell *mini)
{
	int	(**pipes)[2];
	int	i;
	int	n;

	i = 0;
	n = mini->line->cmd_number;
	pipes = &mini->pipes;
	*pipes = malloc((n -1) * sizeof (int [2]));
	if (*pipes == NULL)
	{
		perror(PERROR_MALLOC);
		ft_minishell_exit(mini, EXIT_FAILURE);
	}
	while (i < n -1)
	{
		if (pipe((*pipes)[i]) == -1)
		{
			perror(PERROR_PIPE);
			ft_minishell_exit(mini, EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_connect_pipes_and_redirections(t_minishell *mini, int i)
{
	int	(*pipes)[2];
	int	n;

	pipes = mini->pipes;
	n = mini->line->cmd_number;
	if (i > 0)
	{
		if (dup2(pipes[i -1][READ_END], STDIN_FILENO) == DUP2_ERROR)
		{
			perror(PERROR_DUP2);
			ft_minishell_exit(mini, EXIT_FAILURE);
		}
	}
	if (i < n -1)
	{
		if (dup2(pipes[i][WRITE_END], STDOUT_FILENO) == DUP2_ERROR)
		{
			perror(PERROR_DUP2);
			ft_minishell_exit(mini, EXIT_FAILURE);
		}
	}
	// TODO call redirections (@rub)
}

void	ft_close_pipes(t_minishell *mini)
{
	int	(*pipes)[2];
	int	i;
	int	n;

	i = 0;
	pipes = mini->pipes;
	n = mini->line->cmd_number;
	while (i < n -1)
	{
		close(pipes[i][READ_END]);
		close(pipes[i][WRITE_END]);
		i++;
	}
}
