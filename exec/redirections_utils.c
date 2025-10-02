/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:29:12 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/02 20:13:26 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief checks if a redirection type is input or output
 * @param input sets if the check must be done by input or output
 * @param type redirection type to check
 * @return true if equals, false if not
 */
bool	ft_equals_type(bool input, t_redir_type type)
{
	return ((input && (type == INFILE || type == HERE_DOC))
		|| (!input && (type == OUTFILE || type == OUTFILE_APPEND)));
}

/**
 * @brief returns the flags used for the open function
 * @param type redirection type to check its flags
 * @return the flags needed for open
 */
int	ft_open_options(t_redir_type type)
{
	if (type == INFILE)
		return (O_RDONLY);
	else if (type == OUTFILE)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (type == OUTFILE_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (O_RDONLY);
}
