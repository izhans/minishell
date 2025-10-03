/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:40:16 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/03 12:06:41 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_handle_redirection(t_minishell *mini, int fd, bool input);

void	ft_dup2_redir(t_minishell *mini, t_command *cmd, bool input)
{
	t_list	*node;
	t_redir	*redir;
	int		fd;

	node = cmd->redir;
	fd = -1;
	while (node)
	{
		redir = node->content;
		if (ft_equals_type(input, redir->type))
		{
			if (fd != -1)
				close(fd);
			fd = open(redir->filename, ft_open_options(redir->type), 0644);
			if (fd == -1)
			{
				perror(PERROR_OPEN);
				ft_minishell_exit(mini, EXIT_FAILURE);
			}
			if (redir->type == HERE_DOC)
				unlink(redir->filename);
		}
		node = node->next;
	}
	ft_handle_redirection(mini, fd, input);
}

void	ft_handle_redirection(t_minishell *mini, int fd, bool input)
{
	int	fd2;

	if (input)
		fd2 = STDIN_FILENO;
	else
		fd2 = STDOUT_FILENO;
	if (fd != -1)
	{
		if (dup2(fd, fd2) == DUP2_ERROR)
		{
			perror(PERROR_DUP2);
			ft_minishell_exit(mini, EXIT_FAILURE);
		}
		close(fd);
	}
}

bool	ft_cmd_has_redirection(t_command *cmd, bool input)
{
	t_list	*node;
	t_redir	*redir;

	node = cmd->redir;
	while (node)
	{
		redir = node->content;
		if (ft_equals_type(input, redir->type))
			return (true);
		node = node->next;
	}
	return (false);
}
