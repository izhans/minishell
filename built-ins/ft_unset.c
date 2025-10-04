/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 20:39:41 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/04 21:07:14 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_minishell *mini, t_command *cmd)
{
	t_list	*args;
	char	*key;

	args = cmd->args->next;
	mini->exit_status = 0;
	while (args)
	{
		ft_process_arg(mini, key);
		if (!ft_is_valid_identifier(key))
		{
			printf(BUILTIN_ERROR_IDENTIFIER_UNSET, key);
			mini->exit_status = 1;
			return ;
		}
		ft_remove_envp_var(mini->tenvp, ft_get_envp_var(mini->tenvp, key));
		args = args->next;
	}
}
