/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:40:16 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/08 02:37:59 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_handle_redirection(t_minishell *mini, t_command *cmd,
				int fds[2]);
static bool	ft_open_assign(t_minishell *mini, t_command *cmd, t_redir *redir,
				int fds[2]);
static void	ft_close_all(int *fd_input, int *fd_output, t_redir *redir);

bool	ft_dup2_redir(t_minishell *mini, t_command *cmd)
{
	t_list	*node;
	t_redir	*redir;
	int		fds[2];

	node = cmd->redir;
	fds[0] = -1;
	fds[1] = -1;
	while (node)
	{
		redir = node->content;
		ft_close_all(&fds[0], &fds[1], redir);
		if (!ft_open_assign(mini, cmd, redir, fds))
			return (ft_close_all(&fds[0], &fds[1], NULL), false);
		if (redir->type == HERE_DOC)
			unlink(redir->filename);
		node = node->next;
	}
	ft_handle_redirection(mini, cmd, fds);
	return (true);
}

static void	ft_handle_redirection(t_minishell *mini, t_command *cmd,
	int fds[2])
{
	if (fds[0] != -1)
	{
		if (ft_is_built_in(cmd) && mini->line->cmd_number == 1)
			mini->std_in = dup(STDIN_FILENO);
		if (dup2(fds[0], STDIN_FILENO) == DUP2_ERROR)
		{
			perror(PERROR_DUP2);
			if (!ft_is_built_in(cmd) || mini->line->cmd_number != 1)
				ft_minishell_exit(mini, EXIT_FAILURE);
		}
		close(fds[0]);
	}
	if (fds[1] != -1)
	{
		if (ft_is_built_in(cmd) && mini->line->cmd_number == 1)
			mini->std_out = dup(STDOUT_FILENO);
		if (dup2(fds[1], STDOUT_FILENO) == DUP2_ERROR)
		{
			perror(PERROR_DUP2);
			if (!ft_is_built_in(cmd) || mini->line->cmd_number != 1)
				ft_minishell_exit(mini, EXIT_FAILURE);
		}
		close(fds[1]);
	}
}

static bool	ft_open_assign(t_minishell *mini, t_command *cmd, t_redir *redir,
				int fds[2])
{
	int		fd_tmp;
	bool	builtin;

	builtin = ft_is_built_in(cmd);
	fd_tmp = open(redir->filename, ft_open_options(redir->type), 0644);
	if (redir->type == INFILE || redir->type == HERE_DOC)
		fds[0] = fd_tmp;
	else
		fds[1] = fd_tmp;
	if (fd_tmp == -1)
	{
		perror(PERROR_OPEN);
		mini->exit_status = EXIT_FAILURE;
		if (!builtin || mini->line->cmd_number != 1)
			ft_minishell_exit(mini, mini->exit_status);
		return (false);
	}
	return (true);
}

/**
 * @brief if redir is set to a specific redirections, closes the latest
 * 			opened file descriptor of the same type. if not set it closes both.
 * @param fd_input last opened file descriptor of input
 * @param fd_output last opened file descriptor of output
 */
static void	ft_close_all(int *fd_input, int *fd_output, t_redir *redir)
{
	if ((!redir || (redir->type == INFILE
				|| redir->type == HERE_DOC))
		&& *fd_input != -1)
	{
		close(*fd_input);
		*fd_input = -1;
	}
	if ((!redir || (redir->type == OUTFILE
				|| redir->type == OUTFILE_APPEND))
		&& *fd_output != -1)
	{
		close(*fd_output);
		*fd_output = -1;
	}
}

void	ft_restore_std(t_minishell *mini)
{
	if (mini->line->cmd_number == 1)
	{
		if (mini->std_in != -1)
		{
			if (dup2(mini->std_in, STDIN_FILENO) == DUP2_ERROR)
			{
				perror(PERROR_DUP2);
				ft_minishell_exit(mini, EXIT_FAILURE);
			}
			close(mini->std_in);
		}
		if (mini->std_out != -1)
		{
			if (dup2(mini->std_out, STDOUT_FILENO) == DUP2_ERROR)
			{
				perror(PERROR_DUP2);
				ft_minishell_exit(mini, EXIT_FAILURE);
			}
			close(mini->std_out);
		}
	}
}
