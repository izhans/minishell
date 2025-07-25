/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:09:02 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/25 04:09:37 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*ft_create_t_minishell(char *envp[])
{
	t_minishell	*mini;

	mini = ft_calloc(sizeof(t_minishell), 1);
	if (!mini)
		ft_minishell_exit(NULL);
	mini->envp = ft_str_array_to_str_lst(envp);
	if (!mini->envp)
		ft_minishell_exit(mini);
	return (mini);
}

t_list	*ft_str_array_to_str_lst(char *envp[])
{
	int		i;
	t_list	*list;
	t_list	*node;
	char	*temp;

	i = 0;
	list = NULL;
	while (envp[i])
	{
		temp = ft_strdup(envp[i]);
		if (!temp)
			return (ft_lstclear(&list, &free), NULL);
		node = ft_lstnew(temp);
		if (!node)
			return (free(temp), ft_lstclear(&list, free), NULL);
		ft_lstadd_back(&list, node);
		i++;
	}
	return (list);
}

void	ft_free_t_minishell(t_minishell *mini)
{
	if (mini)
	{
		if (mini->envp)
			ft_lstclear(&(mini->envp), &free);
		if (mini->line)
			ft_free_line(mini->line);
		free(mini);
	}
}
/*
int	main(int argc, char *argv[], char *envp[])
{
	t_minishell *mini = ft_create_t_minishell(envp);
	char *line = readline("minishell> ");
	ft_parser(mini, line);
	ft_free_t_minishell(mini);
}*/