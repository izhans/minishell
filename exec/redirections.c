/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:40:16 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/06 13:02:21 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handle_redirection(t_minishell *mini, t_command *cmd,
	int fd_input, int fd_output);
static bool	ft_open_assign(t_minishell *mini, t_command *cmd, t_redir *redir,
	int *fd_input, int *fd_output);

bool	ft_dup2_redir(t_minishell *mini, t_command *cmd)
{
	t_list	*node;
	t_redir	*redir;
	int		fd_input;
	int		fd_output;

	node = cmd->redir;
	fd_input = -1;
	fd_output = -1;
	while (node)
	{
		redir = node->content;
		if ((redir->type == INFILE || redir->type == HERE_DOC)
			&& fd_input != -1)
			close(fd_input);
		else if ((redir->type == OUTFILE || redir->type == OUTFILE_APPEND)
			&& fd_output != -1)
			close(fd_output);
		if (!ft_open_assign(mini, cmd, redir, &fd_input, &fd_output))
			return (false);
		if (redir->type == HERE_DOC)
			unlink(redir->filename);
		node = node->next;
	}
	ft_handle_redirection(mini,  cmd, fd_input, fd_output);
	return (true);
}

void	ft_handle_redirection(t_minishell *mini, t_command *cmd,
	int fd_input, int fd_output)
{
	bool	builtin;

	builtin = ft_is_built_in(cmd);
	if (fd_input != -1)
	{
		if (!builtin || mini->line->cmd_number != 1)
			mini->std_in = dup(STDIN_FILENO);
		if (dup2(fd_input, STDIN_FILENO) == DUP2_ERROR)
		{
			perror(PERROR_DUP2);
			if (!builtin || mini->line->cmd_number != 1)
				ft_minishell_exit(mini, EXIT_FAILURE);
		}
	}
	if (fd_output != -1)
	{
		if (!builtin || mini->line->cmd_number != 1)
			mini->std_in = dup(STDOUT_FILENO);
		if (dup2(fd_output, STDOUT_FILENO) == DUP2_ERROR)
		{
			perror(PERROR_DUP2);
			if (!builtin || mini->line->cmd_number != 1)
				ft_minishell_exit(mini, EXIT_FAILURE);
		}
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

static bool	ft_open_assign(t_minishell *mini, t_command *cmd, t_redir *redir,
	int *fd_input, int *fd_output)
{
	int	fd;
	bool	builtin;

	builtin = ft_is_built_in(cmd);
	fd = open(redir->filename, ft_open_options(redir->type), 0644);
	if (fd == -1)
	{
		perror(PERROR_OPEN);
		mini->exit_status = EXIT_FAILURE;
		if (!builtin || mini->line->cmd_number != 1)
			ft_minishell_exit(mini, mini->exit_status);
		return (false);
	}
	if (redir->type == INFILE || redir->type == HERE_DOC)
		*fd_input = fd;
	else
		*fd_output = fd;
	return (true);
}
