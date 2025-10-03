/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:36:05 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/03 12:11:10 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_expand_args(t_minishell *mini, t_list *lst_arg);
static bool	ft_expand_redir(t_minishell *mini, t_list *lst_redir);

/**
 * @brief expands and clears a specific variable, argument or redirection.
 * @param mini t_minishell struct to exit in case of error
 * 			, needed for expansion too.
 * @param content holds the string if its an argument, holds the t_redir struct
 * 			if its a redirection, they must be differentiated, see details.
 * @param is_arg set if the variable is an argument.
 * @details HEREDOC must not be cleared in order to differentiate "HERE" 
 * 			and HERE.
 */
bool	ft_expand_clear_var(t_minishell *mini, void *content, bool is_arg)
{
	char	**str;

	if (is_arg)
		str = content;
	else
		str = &((t_redir *)content)->filename;
	if (is_arg || ((t_redir *)content)->type != HERE_DOC)
	{
		*str = ft_expand_var(mini, str, false);
		*str = ft_clear_var(mini, str);
	}
	else if (((t_redir *)content)->type == HERE_DOC)
	{
		if (!ft_register_heredoc(mini, &((t_redir *)content)->filename,
				ft_must_expand(((t_redir *)content)->filename)))
			return (false);
	}
	return (true);
}

/**
 * @brief expands and clears all of the arguments and redirections in a t_line
 * 			struct.
 * @param mini t_minishell struct to exit in case of error, needed for expansion.
 * @param line pointer to t_line struct in order to change its contents.
 */
bool	ft_expand_clear(t_minishell *mini, t_line **line)
{
	t_list	*cmd;

	cmd = (*line)->cmds;
	while (cmd)
	{
		ft_expand_args(mini, ((t_command *)cmd->content)->args);
		if (!ft_expand_redir(mini, ((t_command *)cmd->content)->redir))
			return (false);
		cmd = cmd->next;
	}
	return (true);
}

static void	ft_expand_args(t_minishell *mini, t_list *lst_arg)
{
	while (lst_arg)
	{
		ft_expand_clear_var(mini,
			(char **)(&lst_arg->content), true);
		lst_arg = lst_arg->next;
	}
}

static bool	ft_expand_redir(t_minishell *mini, t_list *lst_redir)
{
	t_redir	*redir;

	while (lst_redir)
	{
		redir = lst_redir->content;
		if (!ft_expand_clear_var(mini, redir, false))
			return (false);
		lst_redir = lst_redir->next;
	}
	return (true);
}
