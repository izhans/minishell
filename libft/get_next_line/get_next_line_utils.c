/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:23:17 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/03 13:30:29 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief frees the line and sets its pointer to NULL
 * @param line a pointer to the line
 */
void	ft_gnl_free(char **line)
{
	free(*line);
	*line = NULL;
}

/**
 * @brief search for a \n
 * @param line the line in which to search
 * @returns 1 if a \n is found, 0 if not
 */
int	ft_gnl_has_new_line(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			return (1);
		line++;
	}
	return (0);
}

/**
 * @brief returns the index after the first \n or the \0 index if there is no \n
 * @param line the line in which to find the \n
 * @returns the index of the \n + 1 OR the length of the string if there is no \n
 * @example a\n	[0:a][1:\n] -> returns 2 (index of \n + 1)
 * @example a	[0:a][1:\0] -> returns 2 (strlen)
 * 								(because it adds 1 before null checking line[i])
 */
int	ft_gnl_where_is_new_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}
