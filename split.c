/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:42:11 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/15 20:34:18 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_parts(char *line, char delimiter);

char	**ft_minishell_split(char *line, char delimiter)
{
	int		i;
	char	comma;
	char	**splitted;
	int		start;
	int		j;

	i = 0;
	comma = 0;
	start = 0;
	j = 0;
	splitted = malloc(sizeof(char *) * (ft_count_parts(line, delimiter) + 1));
	if (splitted == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		ft_comma_check(&comma, line[i]);
		if (comma == 0 && line[i] == delimiter)
		{
			splitted[j] = ft_substr(line, start, i - start);
			start = i + 1;
			j++;
		}
		i++;
	}
	if (line[i] != delimiter)
	{
		splitted[j] = ft_substr(line, start, i - start);
		j++;
	}
	splitted[j] = NULL;
	return (splitted);
}

static int ft_count_parts(char *line, char delimiter)
{
	char	comma;
	int		parts;

	comma = 0;
	parts = 1;
	while (*line != '\0')
	{
		ft_comma_check(&comma, *line);
		if (comma == 0 && *line == delimiter)
			parts++;
		line++;
	}
	return (parts);
}
