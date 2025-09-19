/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:36:14 by isastre-          #+#    #+#             */
/*   Updated: 2025/09/18 17:48:02 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @param n the number of cmds in the pipeline
 */
void	ft_create_pipes(int (**pipes)[2], int n)
{
	// printf("ft_create_pipes %d\n", n);
	int	i;

	i = 0;
	*pipes = malloc((n -1) * sizeof(int[2]));
	if (*pipes == NULL)
	{
		printf("error ft_create_pipes\n");
		exit(1);
	}
	
	while (i < n -1)
	{
		// printf("create pipe[%d]\n", i);

		if (pipe((*pipes)[i]) == -1)
			ft_free_pipes(*pipes);
		i++;
	}
	// printf("end ft_create_pipes\n");
}

void	ft_connect_pipes(int (*pipes)[2], int i, int n)
{
	// printf("ft_connect_pipes i %d n %d\n", i, n);
	
	if (i > 0)
	{
		// printf("dup2 pipe[%d][0]\n", i-1);
		dup2(pipes[i -1][READ_END], STDIN_FILENO);
	}
	if (i < n -1)
	{
		// printf("dup2 pipe[%d][1]\n", n);
		dup2(pipes[i][WRITE_END], STDOUT_FILENO);
	}

	// ft_putstr_fd("pipes connected\n", 2);
}

void	ft_close_pipes(int (*pipes)[2], int n)
{
	// printf("ft_close_pipes %d\n", n);

	int	i;

	i = 0;
	while (i < n -1)
	{
		// printf("close pipe[%d]\n", i);
		// printf("pipe[%d][0]: %d pipe[%d][1]: %d\n", i, pipes[i][0], i, pipes[i][1]);

		close(pipes[i][READ_END]);
		close(pipes[i][WRITE_END]);
		i++;
	}
	// ft_putstr_fd("pipes closed\n", 2);
}

void	ft_free_pipes(int (*pipes)[2])
{
	(void) pipes;
	printf("freeing pipes\n");
}
