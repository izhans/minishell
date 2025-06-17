/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:39:55 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/17 19:49:10 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_empty(char *string);

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	if (argc > 1)
		return (1);
	while (true)
	{
		// read -> is empty -> save
		line = readline("minishell$");
		printf("line: %s\n", line);

		if (ft_is_empty(line))
		{
			free(line);
			continue ;
		}
		
		add_history(line);
		free(line);
	}
}

bool	ft_is_empty(char *string)
{
	int		start;

	if (string == NULL)
		return (true);
	start = 0;
	while (ft_isspace(string[start]) && string[start])
		start++;
	return (start == ft_strlen(string));
}
