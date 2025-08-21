/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:26:33 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/25 22:46:30 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief allocates and returns a t_redir * with information already set up
 * @param line line that contains redirection from the start
 * @param len length of the redirection filename to duplicate
 * @param type type of redirection
 * @return a pointer to t_redir * with information or NULL if calloc went wrong
 */
t_redir	*ft_create_t_redir(char *line, int len, t_type_arg type)
{
	t_redir	*redir;

	redir = ft_calloc(sizeof(t_redir), 1);
	if (!redir)
		return (NULL);
	redir->filename = ft_substr(line, 0, len);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	if (type == IN)
		redir->type = INFILE;
	else if (type == OUT)
		redir->type = OUTFILE;
	else if (type == HERE)
		redir->type = HERE_DOC;
	else if (type == OUT_APPEND)
		redir->type = OUTFILE_APPEND;
	return (redir);
}

/**
 * @brief frees the memory allocated and stored in pointer with t_redir structure
 * @param content pointer to t_redir to free
 */
void	ft_free_redir(void *content)
{
	t_redir	*redir;

	redir = content;
	if (redir)
	{
		if (redir->filename)
			free(redir->filename);
		free(redir);
	}
}
