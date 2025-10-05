/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 20:39:41 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/05 20:02:51 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_minishell *mini, t_command *cmd)
{
	t_list	*args;

	args = cmd->args->next;
	mini->exit_status = 0;
	while (args)
	{
		if (!ft_is_valid_identifier(args->content))
		{
			ft_putendl_fd(BUILTIN_ERROR_IDENTIFIER_UNSET, STDERR_FILENO);
			mini->exit_status = 1;
		}
		ft_remove_envp_var(&mini->tenvp,
			ft_get_envp_var(mini->tenvp, args->content));
		args = args->next;
	}
}
