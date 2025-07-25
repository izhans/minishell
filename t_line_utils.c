/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_line_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:08:41 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/25 04:08:51 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*ft_create_t_line(t_minishell *mini, char *str)
{
	t_line	*line;

	line = ft_calloc(sizeof(t_line), 1);
	if (!line)
		ft_minishell_exit(mini);
	line->line = ft_strdup(str);
	if (!line->line)
		ft_minishell_exit(mini);
	return (line);
}

void	ft_free_line(t_line *line)
{
	if (line->cmds)
		ft_lstclear(&line->cmds, &ft_free_command);
	if (line->line)
		free(line);
}
