/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:36:05 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/02 20:48:47 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
void	ft_expand_clear_var(t_minishell *mini, void *content, bool is_arg)
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
}

/**
 * @brief expands and clears all of the arguments and redirections in a t_line
 * 			struct.
 * @param mini t_minishell struct to exit in case of error, needed for expansion.
 * @param line pointer to t_line struct in order to change its contents.
 */
void	ft_expand_clear(t_minishell *mini, t_line **line)
{
	t_list	*cmd;
	t_list	*lst_arg;
	t_list	*lst_redir;
	t_redir	*redir;

	cmd = (*line)->cmds;
	while (cmd)
	{
		lst_arg = ((t_command *)cmd->content)->args;
		while (lst_arg)
		{
			ft_expand_clear_var(mini,
				(char **)(&lst_arg->content), true);
			lst_arg = lst_arg->next;
		}
		lst_redir = ((t_command *)cmd->content)->redir;
		while (lst_redir)
		{
			redir = lst_redir->content;
			ft_expand_clear_var(mini, redir, false);
			lst_redir = lst_redir->next;
		}
		cmd = cmd->next;
	}
}
