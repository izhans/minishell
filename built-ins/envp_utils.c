/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:33:40 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/04 21:04:38 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief search in the envp a var with the given key and returns it
 * @returns the node if the var exists, NULL otherwise
 */
t_envp	*ft_get_envp_var(t_envp *envp, char *key)
{
	t_envp	*current;

	if (!envp || !key)
		return (NULL);
	current = envp;
	while (current)
	{
		if (ft_equals(current->key, key))
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * @brief tells if an envp var name is valid
 * 	valid names follow the pattern [A-Za-z_][A-Za-z0-9_]
 * @returns true if the name is valid, false otherwise
 */
bool	ft_is_valid_identifier(char *key)
{
	int	i;

	if (!key || !key[0])
		return (false);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (false);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief removes the given node from the envp
 */
void	ft_remove_envp_var(t_envp **envp, t_envp *var)
{
	if (!envp || !*envp || !var)
		return ;
	if (var->prev)
		var->prev->next = var->next;
	else
		*envp = var->next;
	if (var->next)
		var->next->prev = var->prev;
	free(var->key);
	free(var->value);
	free(var);
}
