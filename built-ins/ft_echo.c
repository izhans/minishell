/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:07:13 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/02 18:50:05 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_is_n_option(char *s);

void	ft_echo(t_minishell *mini, t_command *cmd)
{
	t_list	*args;
	bool	n_option;
	bool	space;

	args = cmd->args->next;
	n_option = false;
	while (args && ft_is_n_option(args->content))
	{
		n_option = true;
		args = args->next;
	}
	space = false;
	while (args)
	{
		if (!space)
			space = true;
		else
			ft_putstr(" ");
		ft_putstr(args->content);
		args = args->next;
	}
	if (!n_option)
		ft_putendl("");
	mini->exit_status = 0;
}

static bool	ft_is_n_option(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (false);
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}
