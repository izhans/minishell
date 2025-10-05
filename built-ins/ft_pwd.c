/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:53:05 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/05 19:58:08 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_minishell *mini)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		if (mini->pwd != NULL)
			ft_putendl(mini->pwd);
		else
		{
			mini->exit_status = 1;
			return (ft_putendl_fd(BUILTIN_ERROR_PWD, STDERR_FILENO));
		}
	}
	else
		ft_putendl(pwd);
	mini->exit_status = 0;
}
