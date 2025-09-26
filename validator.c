/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:54:51 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/13 20:18:10 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_validate_redirections(char *str);
static bool	ft_check_redir_parse(char *str, int *i);
static bool	ft_check_redir_file(char *str);
static bool	ft_validate_cmds(t_minishell *mini, t_line *line);

/**
 * @brief validates whether a t_line struct is valid after parsing. Errors
 * 			with bad specification of redirections and empty commands are
 * 			checked.
 * @param line t_line struct to check parsing.
 * @return true if its a valid parse and no errors are found, false otherwise.
 */
bool	ft_validate(t_minishell *mini, t_line *line)
{
	if (!ft_validate_redirections(line->line))
		return (printf(ERROR_MSG_REDIRECTION), false);
	if (!ft_validate_cmds(mini, line))
		return (printf(ERROR_MSG_PIPES), false);
	return (true);
}

/**
 * @brief checks if a string has all valid redirectons, checking if is a valid
 * 			representation of a redirection and also if there is no 
 * 			empty redirection.
 * @param str string to check.
 * @return true if its valid, false if not.
 */
static bool	ft_validate_redirections(char *str)
{
	int		i;
	char	comma;

	i = 0;
	comma = 0;
	while (str[i])
	{
		ft_comma_check(&comma, str[i]);
		if (comma == 0 && ft_is_redir(str[i])
			&& (!ft_check_redir_parse(&str[i], &i)
				|| !ft_check_redir_file(&str[i])))
			return (false);
		else
			i++;
	}
	return (true);
}

/**
 * @brief checks whether a string has a valid redirection characters. '<<<'
 * 			is not valid. '<>' isnt either.
 * @param str pointer to string that starts at the redirection to check.
 * @param i pointer to index to increment all of the checked characters.
 * @return true if its valud, false if not.
 */
static bool	ft_check_redir_parse(char *str, int *i)
{
	int	j;

	j = 0;
	while (ft_is_redir(str[j]))
		j++;
	(*i) += j;
	if (j > 2)
		return (false);
	else if (j == 2 && (ft_strncmp(str, "<>", 2) == 0
			|| ft_strncmp(str, "><", 2) == 0))
		return (false);
	return (true);
}

/**
 * @brief checks whether an identified valid representation of a redirecion
 * 			has a specified name. This means 'echo < | grep' is NOT valid.
 * 			its not valid to not give a name before the string ends or another
 * 			command is started (with '|'), or before another redirection
 * 			metacharacter.
 * @param str string to check after the valid representation of redirection.
 * @return true if the filename has been found,
 * 			false if no name or empty name (is empty if it is "" or '').
 */
static bool	ft_check_redir_file(char *str)
{
	int	j;

	j = 0;
	while (ft_isspace(str[j]))
		j++;
	return (str[j] != '\0' && str[j] != '|' && !ft_is_redir(str[j]));
}

/**
 * @brief validates if all of the commands are valid. This checks if the
 * 			commands have at least one argument and their redirections have
 * 			at least one character after cleaning the SIMPLE_COMMA
 * 			and DOUBLE_COMMA.
 * @param line t_line struct to check args of every cmd.
 * @return true if its valid, false if there is one command without arguments.
 */
static bool	ft_validate_cmds(t_minishell *mini, t_line *line)
{
	t_list	*cmd;
	t_list	*redir;
	char	*str;

	cmd = line->cmds;
	while (cmd)
	{
		if (ft_lstsize(((t_command *)cmd->content)->args) == 0)
			return (false);
		redir = ((t_command *)cmd->content)->redir;
		while (redir)
		{
			str = ft_strdup(((t_redir *)redir->content)->filename);
			if (str == NULL)
				ft_minishell_exit(mini, EXIT_FAILURE);
			if (((t_redir *)redir->content)->type != HERE_DOC)
				ft_expand_clear_var(mini, &str, true);
			if (ft_strlen(str) == 0)
				return (free(str), false);
			free(str);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (true);
}
