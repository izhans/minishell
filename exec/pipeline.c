/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:36:14 by isastre-          #+#    #+#             */
/*   Updated: 2025/09/26 13:31:19 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @param n the number of cmds in the pipeline
 */
void	ft_create_pipes(t_minishell *mini, int (**pipes)[2], int n)
{
	int	i;

	i = 0;
	*pipes = malloc((n -1) * sizeof(int[2]));
	if (*pipes == NULL)
	{
		perror(PERROR_PIPE);
		ft_minishell_exit(mini, 1);
	}
	while (i < n -1)
	{
		if (pipe((*pipes)[i]) == -1)
			ft_free_pipes(*pipes, n);
		i++;
	}
}

void	ft_connect_pipes(int (*pipes)[2], int i, int n)
{
	// TODO dup2 errors
	if (i > 0)
	{
		dup2(pipes[i -1][READ_END], STDIN_FILENO);
	}
	if (i < n -1)
	{
		dup2(pipes[i][WRITE_END], STDOUT_FILENO);
	}
}

void	ft_close_pipes(int (*pipes)[2], int n)
{
	int	i;

	i = 0;
	while (i < n -1)
	{
		close(pipes[i][READ_END]);
		close(pipes[i][WRITE_END]);
		i++;
	}
}

void	ft_free_pipes(int (*pipes)[2], int n)
{
	int	i;

	i = 0;
	while (i < n -1)
	{
		free(pipes[i]);
		i++;
	}
}
