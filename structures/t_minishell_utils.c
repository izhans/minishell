/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:09:02 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/27 16:01:30 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief allocates and copies envp in t_minishell struct
 * @param envp environmental variables
 * @return t_minishell pointer with envp copied in a list
 */
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

/**
 * @brief transforms array of strings into a dynamic allocated list
 * @param strs array of strings
 * @return pointer to list
 */
t_list	*ft_str_array_to_str_lst(char *strs[])
{
	int		i;
	t_list	*list;
	t_list	*node;
	char	*temp;

	i = 0;
	list = NULL;
	while (strs[i])
	{
		temp = ft_strdup(strs[i]);
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

/**
 * @brief frees allocated t_minishell struct
 * @param mini struct t_minishell to free
 */
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
