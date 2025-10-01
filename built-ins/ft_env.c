/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:29:37 by isastre-          #+#    #+#             */
/*   Updated: 2025/09/30 15:32:41 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_minishell *mini)
{
	t_list	*current;

	current = mini->envp;
	while (current)
	{
		ft_putendl(current->content);
		current = current->next;
	}
	mini->exit_status = 0; // TODO ver que exit status toca
}
