/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:53:05 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/02 15:02:21 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_minishell *mini)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl(pwd);
	mini->exit_status = 0;
}
