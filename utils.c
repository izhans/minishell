/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:09:55 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/25 04:11:28 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief exits the minishell after liberating the memory allocated.
 * @param mini struct with access to allocated variables
 */
void	ft_minishell_exit(t_minishell *mini)
{
	if (mini)
		ft_free_t_minishell(mini);
	exit(1);
}

/**
 * @brief checks if the line_char is any type of comma and updates comma status
 *              if the comma has a status, checks if line_char has the same 
 * 				status and updates comma status to null
 *              * status refers to the comma ascii code
 * @param comma a pointer to the variable that stores the comma_status
 * @param line_char the char being read from the line
 */
void	ft_comma_check(char *comma, char line_char)
{
	if (*comma == 0 && (line_char == SIMPLE_COMMA
			|| line_char == DOUBLE_COMMA))
		*comma = line_char;
	else if (line_char == *comma)
		*comma = 0;
}
