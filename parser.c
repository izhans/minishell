/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 04:07:48 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/25 04:08:10 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_command_parser(t_minishell *mini, char *line);

/**
 * 
 */
t_line	*ft_parser(t_minishell *mini, char *line)
{
	t_line	*parsed;

	printf("PARSER WITH %s.\n", line);
	parsed = ft_create_t_line(mini, line);
	parsed->cmds = ft_command_parser(mini, line);
	return (parsed);
}

t_list	*ft_command_parser(t_minishell *mini, char *line)
{
	int		i;
	char	comma;
	int		start;
	t_list	*cmds;

	i = 0;
	start = 0;
	comma = 0;
	cmds = NULL;
	while (line[i])
	{
		ft_comma_check(&comma, line[i]);
		if (line[i] == PIPE && comma == 0)
		{
			printf("Command: [%s]\n", ft_substr(line, start, i - start));
			start = i + 1;
		}
		i++;
	}
	printf("Command: [%s]\n", ft_substr(line, start, i - start));
	return (NULL);
}
