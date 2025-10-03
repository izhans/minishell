/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:52:01 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/03 12:24:22 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_transform_exit_status(char *n);

/**
 * @brief exit built-in
 * exits with the specified exit_status
 * exits with the last exit_status if no exit_status is passed
 */
void	ft_exit(t_minishell *mini, t_command *cmd)
{
	int			exit_status;

	exit_status = mini->exit_status;
	if (ft_lstsize(cmd->args) > 2)
	{
		mini->exit_status = EXIT_FAILURE;
		return (ft_putendl_fd(BUILTIN_ERROR_ARGS_EXIT, STDERR_FILENO));
	}
	else if (cmd->args->next != NULL)
		exit_status = ft_transform_exit_status(cmd->args->next->content);
	ft_minishell_exit(mini, exit_status);
}

static int	ft_transform_exit_status(char *n)
{
	int	i;

	i = 0;
	if (n[i] == '-' || n[i] == '+')
		i++;
	while (n[i])
	{
		if (!ft_isdigit(n[i]))
			return (MAX_EXIT_STATUS);
		i++;
	}
	return (ft_atoi(n) % MAX_EXIT_STATUS);
}
