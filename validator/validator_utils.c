/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 21:01:05 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/04 21:02:12 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
bool	ft_check_redir_file(char *str)
{
	int	j;

	j = 0;
	while (ft_isspace(str[j]))
		j++;
	return (str[j] != '\0' && str[j] != '|' && !ft_is_redir(str[j]));
}

