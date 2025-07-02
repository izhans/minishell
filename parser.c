/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:29:06 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/02 20:42:54 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_minishell_split(char *line, char delimiter);

/**
*	@param line Receives a non-null not empty line.
*/
t_line	ft_parse(char *line)
{
	
}

void ft_comma_check(char *comma, char line_char)
{
	if (*comma == 0 && (line_char == SIMPLE_COMMA || line_char == DOUBLE_COMMA))
		*comma = line_char;
	else if (line_char == *comma)
		*comma = 0;
}

int ft_count_parts(char *line, char delimiter)
{
	char	comma;
	int		parts;
	bool	in_delimiter;

	comma = 0;
	parts = 1;
	in_delimiter = false;
	while (*line != '\0')
	{
		ft_comma_check(&comma, *line);
		if (comma == 0 && !in_delimiter && *line == delimiter)
			in_delimiter = true;
		else if (comma == 0 && in_delimiter && *line != delimiter)
		{
			parts++;
			in_delimiter = false;
		}
		line++;
	}
	return (parts);
}

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
		if (comma == 0 && line[i] == delimiter && start != i)
		{
			splitted[j] = ft_substr(line, start, i - start);
			start = i + 1;
			j++;
		}
		else if (comma == 0 && line[i] == delimiter)
			start = i + 1;
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

int main(int argc, char **argv)
{
	char **splitted = ft_minishell_split(argv[1], ' ');
	printf("Partes: %d", ft_count_parts(argv[1], ' '));
	while (*splitted)
	{
		printf(">%s|\n", *splitted);
		splitted++;	
	}
}