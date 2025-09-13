/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:24:33 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/13 20:18:59 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_copy_exp(t_minishell *mini, char *new, char *str, int *i);
static int	ft_expand_len(t_minishell *mini, char *str, bool is_heredoc);

/**
 * @brief expands a string, according to environmental variables and last exit
 * 			status.
 * @param mini t_minishell struct to exit in case of error.
 * @param str pointer to a not cleared string, must be freed before returning.
 * @param is_heredoc set if the variable is a heredoc line.
 * @return the new expanded string.
 * @details  a expanded string is a string with the $(NAME) expanded to the
 * 			content of the environmental variable NAME=content, can also expand
 * 			$? as the last exit status. Heredoc must be treated differently as
 * 			it always expands $(NAME) even if it is inside ''.
 */
char	*ft_expand_var(t_minishell *mini, char **str, bool is_heredoc)
{
	char	*new;
	char	comma;
	int		i;
	int		j;

	new = ft_calloc(ft_expand_len(mini, *str, is_heredoc) + 1, sizeof(char));
	if (!new)
		ft_minishell_exit(mini, EXIT_FAILURE);
	i = 0;
	comma = 0;
	j = 0;
	while ((*str)[i])
	{
		ft_comma_check(&comma, (*str)[i]);
		if ((*str)[i] == '$' && (is_heredoc || comma != SIMPLE_COMMA))
			i += ft_copy_exp(mini, new, &(*str)[i + 1], &j);
		else
		{
			new[j] = (*str)[i];
			j++;
		}
		i++;
	}
	free(*str);
	return (new);
}

/**
 * @brief copies content from a word found at str to the new, expanded one.
 * 			using environmental value or last exit status.
 * @param mini t_minishell struct to exit in case of error.
 * @param new destination of copy, start of the string.
 * @param str string starts at the name of the environmental variable to
 * 			expand (or last exit status).
 * @param j must be incremented as many letters have been written in new.
 * @return the length of the name to increment index of original string.
 */
static int	ft_copy_exp(t_minishell *mini, char *new, char *str, int *j)
{
	int		name_len;
	char	*word;

	if (str[0] != '?')
		word = ft_word(mini, str);
	else
	{
		word = ft_itoa(mini->exit_status);
		if (!word)
		{
			free(new);
			ft_minishell_exit(mini, EXIT_FAILURE);
		}
	}
	if (word != NULL)
		ft_strlcpy(&new[*j], word, ft_strlen(word) + 1);
	name_len = ft_word_name_len(str);
	if (name_len == 0)
		return (new[*j] = '$', (*j)++, 0);
	(*j) += ft_strlen(word);
	if (str[0] == '?')
		free(word);
	return (name_len);
}

/**
 * @brief calculates the length of the expanded string.
 * @brief str string to calculate its new length.
 * @return length of the cleared string.
 */
int	ft_expand_len(t_minishell *mini, char *str, bool is_heredoc)
{
	int		i;
	int		len;
	char	comma;

	i = 0;
	comma = 0;
	len = 0;
	while (str != NULL && str[i])
	{
		ft_comma_check(&comma, str[i]);
		if (str[i] == '$' && (is_heredoc || comma != SIMPLE_COMMA))
		{
			len += ft_word_len(mini, &str[i + 1]);
			i += ft_word_name_len(&str[i + 1]);
		}
		else
			len++;
		i++;
	}
	return (len);
}
