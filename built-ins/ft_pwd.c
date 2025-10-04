/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:53:05 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/04 22:50:10 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_minishell *mini)
{
	if (mini->pwd != NULL)
		ft_putendl(mini->pwd);
	else
		//ERROR.
	mini->exit_status = 0;
}
