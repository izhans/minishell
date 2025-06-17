/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:39:55 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/17 19:27:13 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_empty(char *string);

int main(int argc, char **argv, char **envp)
{
	if (argc > 1)
		return (1);
	char *line;
	while (true)
	{
		// read -> is empty -> save
		line = readline("minishell$");
		printf("line: %s\n", line);

		if (ft_is_empty(line))
		{
			free(line);
			continue;
		}
		
		add_history(line);
		free(line);
	}
}

bool	ft_is_empty(char *string)
{
	int		start;
	int		end;

	if (string == NULL)
		return (true);
	start = 0;
	end = ft_strlen(string);
	while (ft_isspace(string[start]) && string[start])
		start++;
	return (start == end);
}
