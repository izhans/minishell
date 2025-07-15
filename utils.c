/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:11:23 by isastre-          #+#    #+#             */
/*   Updated: 2025/07/15 19:19:05 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief checks if the line_char is any type of comma and updates comma status.
 * 		if the comma has a status, checks if line_char has the same status and
 * 		 updates comma status to null
 * 		* status refers to the comma ascii code
 * @param comma a pointer to the variable that stores the comma_status
 * @param line_char the char being read from the line
 */
void ft_comma_check(char *comma, char line_char)
{
	if (*comma == 0 && (line_char == SIMPLE_COMMA || line_char == DOUBLE_COMMA))
		*comma = line_char;
	else if (line_char == *comma)
		*comma = 0;
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
