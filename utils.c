/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:09:55 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/13 20:11:22 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief exits the minishell after liberating the memory allocated.
 * @param mini struct with access to allocated variables
 */
void	ft_minishell_exit(t_minishell *mini, int exit_status)
{
	if (mini)
		ft_free_t_minishell(mini);
	exit(exit_status);
}

/**
 * @brief checks if the given string is empty
 *			(has content which is not any type of space)
 * @param string the string to check
 * @returns true if the string is considered empty, false if not
 */
bool	ft_is_empty(char *string)
{
	size_t		start;

	if (string == NULL)
		return (true);
	start = 0;
	while (ft_isspace(string[start]) && string[start])
		start++;
	return (start == ft_strlen(string));
}
