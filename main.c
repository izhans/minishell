/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:39:55 by isastre-          #+#    #+#             */
/*   Updated: 2025/07/15 19:20:41 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_empty(char *string);

int	main(int argc, char **argv, char **envp)
{
	(void) argc, (void) argv, (void) envp;
	char	*line;
	t_line	*parsed;

	if (argc > 1)
		return (1);
	while (true)
	{
		// read -> is empty -> save
		line = readline("minishell$ ");
		printf("line: %s\n", line);

		if (ft_is_empty(line))
		{
			free(line);
			continue ;
		}
		parsed = ft_parse(line);
		
		add_history(line);
		free(line);
		ft_free_tline(parsed);
	}
}

