/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:50:49 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/04 00:40:21 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_split_key_value(char *var, char **key, char **value);

t_envp	*ft_init_envp(char **envp)
{
	t_envp	*lst;
	t_envp	*node;
	int		i;
	char	*key;
	char	*value;

	lst = NULL;
	i = 0;
	while (envp[i])
	{
		ft_split_key_value(envp[i], &key, &value);
		node = ft_envp_new(key, value);
		if (!node)
		{
			ft_envp_clear(&lst);
			return (NULL);
		}
		ft_envp_add_back(&lst, node);
		i++;
	}
	return (lst);
}

static void	ft_split_key_value(char *var, char **key, char **value)
{
	// TODO malloc errors
	char	*split;

	split = ft_strchr(var, '=');
	if (!split)
	{
		*key = ft_strdup(var);
		*value = NULL;
	}
	else
	{
		*key = ft_substr(var, 0, split - var);
		*value = ft_strdup(split + 1);
	}
}

t_envp	*ft_envp_new(char *key, char *value)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	if (node == NULL)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_envp_add_back(t_envp **lst, t_envp *new)
{
	t_envp	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_envp_clear(t_envp **lst)
{
	t_envp	*tmp;
	t_envp	*next;

	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}
