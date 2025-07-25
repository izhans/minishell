/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:08:22 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/25 04:08:36 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_command(void *content)
{
	t_command	*cmd;

	cmd = content;
	if (cmd->args)
		ft_lstclear(&cmd->args, &free);
	if (cmd->path)
		free(cmd->path);
	if (cmd->redir)
		ft_lstclear(&cmd->redir, &free);
}
