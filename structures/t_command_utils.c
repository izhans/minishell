/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:08:22 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/13 20:21:20 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief allocates a t_command struct
 * @param mini t_minishell struct to free in case of error
 * @return pointer to t_command struct
 */
t_command	*ft_create_t_command(t_minishell *mini)
{
	t_command	*cmd;

	cmd = ft_calloc(sizeof(t_command), 1);
	if (!cmd)
		ft_minishell_exit(mini, EXIT_FAILURE);
	return (cmd);
}

/**
 * @brief frees content of a t_command struct from a generic pointer.
 * @param content generic void * pointer to t_command struct to free
 */
void	ft_free_command(void *content)
{
	t_command	*cmd;

	cmd = content;
	if (cmd)
	{
		if (cmd->args)
			ft_lstclear(&cmd->args, &free);
		if (cmd->path)
			free(cmd->path);
		if (cmd->redir)
			ft_lstclear(&cmd->redir, &ft_free_redir);
		if (cmd->cmd_str)
			free(cmd->cmd_str);
		free(cmd);
	}
}
