/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:09:55 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/03 13:50:15 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief exits the minishell after liberating the memory allocated.
 * @param mini struct with access to allocated variables
 */
void	ft_minishell_exit(t_minishell *mini, int exit_status)
{
	rl_clear_history();
	if (mini)
		ft_free_t_minishell(mini);
	exit(exit_status);
}

/**
 * @brief checks if the given string is empty
 *			(has content which is not any type of space)
 * @param string the string to check
 * @returns true if the string is considered empty, false if not
 */
bool	ft_is_empty(char *string)
{
	size_t		start;

	if (string == NULL)
		return (true);
	start = 0;
	while (ft_isspace(string[start]) && string[start])
		start++;
	return (start == ft_strlen(string));
}

/**
 * @brief returns the line using readline or gnl depending on the mode.
 * @return string with the read line.
 */
char	*ft_readline_mini(t_minishell *mini, char *prompt)
{
	char	*str;
	char	*trim;

	if (isatty(STDIN_FILENO))
		return (readline(prompt));		
	else
	{
		str = get_next_line(STDIN_FILENO);
		if (str == NULL)
			return (NULL);
		trim = ft_strtrim(str, "\n");
		if (trim == NULL)
			ft_minishell_exit(mini, EXIT_FAILURE);
		free(str);
		return (trim);
	}
}
