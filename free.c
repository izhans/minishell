/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:20:57 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/09 20:31:39 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_free_tcommand(t_commmand **cmd, int cmd_number);

/**
 * @brief frees a t_line struct and its data
 * @param line the t_line to free
 */
void ft_free_tline(t_line *line)
{
	if (line != NULL)
	{
		ft_free_str_array(line->splited);
		if (line->cmds != NULL)
			ft_free_tcommand(line->cmds, line->cmd_number);
		free(line);
	}
}
/**
 * @brief frees a t_command struct and its data
 * @param cmd the t_command array to free
 * @param cmd_number the number of cmds in the cmd array
 */
static void ft_free_tcommand(t_commmand **cmd, int cmd_number)
{
	int	i;

	i = 0;
	while (i < cmd_number)
	{
		ft_free_str_array(cmd[i]->args);
		if (cmd[i]->infile != NULL)
			free(cmd[i]->infile);
		if (cmd[i]->outfile != NULL)
			free(cmd[i]->outfile);
		if (cmd[i]->path != NULL)
			free(cmd[i]->path);
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
