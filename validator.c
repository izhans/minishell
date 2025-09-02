/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:54:51 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/09/02 20:50:17 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * @brief checks if a string is valid for parsing.
 * @param str string to check
 * @return true if its valid, false if not.
 */
bool	ft_validate(char *str)
{
	int		i;
	char	comma;

	i = 0;
	comma = 0;
	while (str[i])
	{
		ft_comma_check(&comma, str[i]);
		if (comma == 0 && ft_is_redir(str[i])
			&& !ft_check_redir_parse(&str[i], &i))
			return (false);
		i++;
	}
	return (true);
}
