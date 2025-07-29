/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:07:48 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/29 19:22:53 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_command_parser(t_minishell *mini, char *line);
void	ft_lst_add_cmd(t_minishell *mini, t_list **lst, char *line, int len);
void	ft_args_parser(t_minishell *mini, char *line, t_command **cmd);
bool	ft_word_recognition(char *line, char *comma, int len);
t_list	*ft_add_to_list(t_command **cmd, char *line, int len, t_type_arg *type);

/**
 * @brief parser that returns a t_line struct with 
 * 			all the commands and information
 * @param mini t_minishell struct to free in case of error
 * @param line string to parse, analize commands from line
 * @return t_line pointer struct with all the parsing
 */
t_line	*ft_parser(t_minishell *mini, char *line)
{
	t_line	*parsed;

	parsed = ft_create_t_line(mini, line);
	parsed->cmds = ft_command_parser(mini, line);
	return (parsed);
}

/**
 * @brief parses every command (must be separated by PIPE) and after recognizing
 * 			every command, calls an argument parser.
 * @param mini t_minishell struct to free in case of error
 * @param line string to parse
 */
static t_list	*ft_command_parser(t_minishell *mini, char *line)
{
	int		i;
	char	comma;
	int		start;
	t_list	*cmds;

	i = 0;
	start = 0;
	comma = 0;
	cmds = NULL;
	while (line[i])
	{
		ft_comma_check(&comma, line[i]);
		if (line[i] == PIPE && comma == 0)
		{
			ft_lst_add_cmd(mini, &cmds, &line[start], i - start);
			start = i + 1;
		}
		i++;
	}
	ft_lst_add_cmd(mini, &cmds, &line[start], i - start);
	return (cmds);
}

/**
 * @brief parses every command to check and add arguments and redirections,
 * 			creating a t_command pointer and adding it to the list
 * @param mini t_minishell struct to free in case of error
 * @param lst list to add the t_commands
 * @param line string at the start of the command
 * @param len length of the command
 */
static void	ft_lst_add_cmd(t_minishell *mini, t_list **lst, char *line,
	int len)
{
	char		*substr;
	t_command	*cmd;
	t_list		*new;

	substr = ft_substr(line, 0, len);
	if (!substr)
		ft_minishell_exit(mini);
	cmd = ft_create_t_command(mini);
	ft_args_parser(mini, substr, &cmd);
	new = ft_lstnew(cmd);
	if (!new)
		ft_minishell_exit(mini);
	ft_lstadd_back(lst, new);
	free(substr);
}

/**
 * @brief parses the words on a command string and adds it to the corresponding
 * 			list inside the t_command struct
 * @param mini t_minishell struct to free in case of error
 * @param line string that holds the command line
 * @param cmd pointer to the t_command structure, to add args and redirections
 */
static void	ft_args_parser(t_minishell *mini, char *line, t_command **cmd)
{
	int			i;
	char		comma;
	int			start;
	t_type_arg	type;

	i = 0;
	comma = 0;
	start = 0;
	type = NONE;
	while (line[i])
	{
		if (ft_word_recognition(&line[start], &comma, i - start)
			&& !ft_add_to_list(cmd, &line[start], i - start, &type))
			ft_minishell_exit(mini);
		ft_next_checker(&type, comma, line[i]);
		if ((ft_isspace(line[i]) || ft_is_redir(line[i])) && comma == 0)
			start = i + 1;
		i++;
	}
	if (ft_word_recognition(&line[start], &comma, i - start)
		&& !ft_add_to_list(cmd, &line[start], i - start, &type))
		ft_minishell_exit(mini);
}

/**
 * @brief checks if a word ending has been found, checks if the comma status
 * 			has changed
 * 			* word ending is found by SPACE, '<' and '>' or by the end of
 * 			the string. Length of a word cant be 0. 
 * 			(if there are to word-endings together there is no word)
 * @param line start of the word in the command string
 * @param comma pointer to value of comma_status
 * @param len length of the word
 * @return true if a word is found, false otherwise
 */
static bool	ft_word_recognition(char *line, char *comma, int len)
{
	bool	found;

	found = false;
	ft_comma_check(comma, line[len]);
	if ((ft_isspace(line[len]) || ft_is_redir(line[len]) || line[len] == 0)
		&& *comma == 0 && len > 0)
		found = true;
	return (found);
}
