/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:46:41 by isastre-          #+#    #+#             */
/*   Updated: 2025/07/15 20:28:49 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_count_cmds(char **cmds);

/**
 * @param parsed the parsed line
 */
bool	ft_validator(t_line *parsed)
{
	printf("Line: %s\n", parsed->line);
	if (ft_count_cmds(parsed->splited) != parsed->cmd_number)
		return (false);
	return (true);
}

/**
 * @brief counts the real number of cmds
 * @param line the line to check
 * @param delimiter the delimiter that separates cmds.
 */
static int ft_count_cmds(char **cmds)
{
	int	i;
	int	parts;

	i = 0;
	parts = 0;
	while (cmds[i] != NULL)
	{
		if (!ft_is_empty(cmds[i]))
			parts++;
		i++;
	}
	return (parts);
}
