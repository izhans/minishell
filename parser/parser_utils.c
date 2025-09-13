/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:21:12 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/10 22:44:35 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list *ft_list_create(char *line, int len, t_type_arg *type);

/**
 * @brief adds to the corresponding list of the t_command struct the word
 * 			that has been found.
 * @param cmd t_command struct to add the word.
 * @param line start of the word at the command line.
 * @param len length of the word.
 * @param type pointer type of word (argument or redirection).
 * @return pointer to the new t_list containing the word or NULL if an error
 * 			was encountered.
 */
t_list	*ft_add_to_list(t_command **cmd, char *line, int len, t_type_arg *type)
{
	t_list	*new;

	new = ft_list_create(line, len, type);
	if (!new)
		return (NULL);
	if (*type == ARG)
		ft_lstadd_back(&(*cmd)->args, new);
	else
		ft_lstadd_back(&(*cmd)->redir, new);
	*type = NONE;
	return (new);
}

/**
 * @brief creates the t_list node with needed information depending on the type
 * 		(if it is an ARGument creates a str, if its a redirection creates 
 * 		content with t_redir).
 * @param line start of the word at the command line.
 * @param len length of the word.
 * @param type pointer type of word (argument or redirection).
 * @return the t_list struct with needed information (str/t_redir pointer).
 */
static t_list *ft_list_create(char *line, int len, t_type_arg *type)
{
	char	*temp;
	t_redir	*redir;
	t_list	*new;

	if (*type == ARG)
	{
		temp = ft_substr(line, 0, len);
		if (!temp)
			return (NULL);
		new = ft_lstnew(temp);
		if (!new)
			return (free(temp), NULL);
	}
	else
	{
		redir = ft_create_t_redir(line, len, *type);
		if (!redir)
			return (NULL);
		new = ft_lstnew(redir);
		if (!new)
			return (ft_free_redir(redir), NULL);
	}
	return (new);
}

/**
 * @brief checks if a type of argument must be updated after founding a 
 * 			metacharacter.
 * 			it cant be updated if it is inside any quote, as they are
 * 			refering to the literal char.
 * @param type pointer to the type of argument.
 * @param comma pointer to value of comma_status.
 * @param line_char the char found in the line.
 */
void	ft_next_checker(t_type_arg *type, char comma, char line_char)
{
	if (comma == 0)
	{
		if (*type != IN && line_char == '<')
			*type = IN;
		else if (*type == IN && line_char == '<')
			*type = HERE;
		else if (*type != OUT && line_char == '>')
			*type = OUT;
		else if (*type == OUT && line_char == '>')
			*type = OUT_APPEND;
		else if (*type == NONE)
			*type = ARG;
	}
}

/**
 * @brief checks if a letter is the metacharacter for any redirection.
 * @param c char casted to int.
 * @return true if it is a redirectiom, false if it is not.
 */
bool	ft_is_redir(int c)
{
	return (c == '<' || c == '>');
}

/**
 * @brief checks if the line_char is any type of comma and updates comma status
 *              if the comma has a status, checks if line_char has the same 
 * 				status and updates comma status to null.
 *              * status refers to the comma ascii code.
 * @param comma a pointer to the variable that stores the comma_status.
 * @param line_char the char being read from the line.
 */
void	ft_comma_check(char *comma, char line_char)
{
	if (*comma == 0 && (line_char == SIMPLE_COMMA
			|| line_char == DOUBLE_COMMA))
		*comma = line_char;
	else if (line_char == *comma)
		*comma = 0;
}

