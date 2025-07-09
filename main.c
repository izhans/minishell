/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:39:55 by isastre-          #+#    #+#             */
/*   Updated: 2025/07/09 19:00:04 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_empty(char *string);

int	main(int argc, char **argv, char **envp)
{
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
		/*int k = 0;
		printf("Number of commands: %d\n", parsed->cmd_number);
		int ki = 0;
		while (parsed->splited[ki] != NULL)
		{
			printf("Command %d: %s\n", k, parsed->splited[ki]);
			printf("Args:\n");
			int k2 = 0;
			while (parsed->cmds[k].args[k2])
			{
				printf("%s\n", parsed->cmds[k].args[k2]);
				k2++;
			}
			if (parsed->cmds[k].infile != NULL)
				printf("Infile: %s\n", parsed->cmds[k].infile);
			if (parsed->cmds[k].outfile != NULL)
				printf("Outfile: %s\n", parsed->cmds[k].outfile);
			k++;
			ki++;
		}*/
		add_history(line);
		free(line);
		ft_free_tline(parsed);
	}
}

/**
 * @brief checks if the given string is empty
 *			(has content which is not any type of space)
 * @param string the string to check
 * @returns true if the string is considered empty, false if not
 */
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
