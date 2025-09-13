/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_line_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:08:41 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/13 20:21:47 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief allocates a t_line struct and assigns a duplicated str as line
 * @param mini t_minishell struct to free in case of error
 * @param str line to duplicate and assign
 */
t_line	*ft_create_t_line(t_minishell *mini, char *str)
{
	t_line	*line;

	line = ft_calloc(sizeof(t_line), 1);
	if (!line)
		ft_minishell_exit(mini, EXIT_FAILURE);
	line->line = ft_strdup(str);
	if (!line->line)
		ft_minishell_exit(mini, EXIT_FAILURE);
	return (line);
}

/**
 * @brief free a t_line struct
 * @param line pointer to t_line struct to free
 */
void	ft_free_line(t_line *line)
{
	if (line)
	{
		if (line->cmds)
			ft_lstclear(&(line->cmds), &ft_free_command);
		if (line->line)
			free(line->line);
		free(line);
	}
	line = NULL;
}
