/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:09:02 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/02 19:19:24 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../minishell.h"

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
 * @brief transforms a dynamic allocated str list into an array of strings
 * @param list a str list
 * @returns a str array with the list contents, NULL if error
 */
char	**ft_str_list_to_str_array(t_list *list)
{
	int		size;
	char	**array;
	int		i;

	size = ft_lstsize(list);
	array = malloc(size * sizeof(char *) +1);
	if (array == NULL)
		return (NULL);
	i = 0;
	while (list != NULL)
	{
		array[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
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
