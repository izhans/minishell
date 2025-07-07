/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:29:06 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/07 20:57:28 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_process_command(char *split, t_commmand *command);

/**
*	@param line Receives a non-null not empty line.
*/
t_line	*ft_parse(char *line)
{
	t_line *parsed;

	parsed = malloc(sizeof(t_line));
	if (parsed == NULL)
		return (NULL);
	parsed->line = line;
	parsed->splited = ft_minishell_split(line, '|');
	
}

int ft_count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

t_commmand *ft_command_parser(char **split)
{
	t_commmand	*command;
	int			i;

	command = malloc(sizeof(t_commmand) * (ft_count_split(split) + 1));
	if (command == NULL)
		return (NULL);
	i = 0;
	while (split[i])
	{
		ft_process_command(split[i], &command[i]);
		i++;
	}
}

void ft_process_command(char *split, t_commmand *command)
{
	char	**splitcmd;
	int		i;

	splitcmd = ft_minishell_split(split, ' ');
	i = 0;
	while (splitcmd[i])
	{
		command->path = NULL;
		// command->args = 
	}
	
}

int		ft_count_args(char **split)
{
	int	i;
	int	count;
	bool	redirection;

	i = 0;
	count = 0;
	redirection = false;
	while (split[i] != NULL)
	{
		printf("i: %d %s\n", i, split[i]);
		if (split[i][0] == '<' || split[i][0] == '>')
		{
			if (ft_strlen(split[i]) == 1)
				redirection = true;
		}
		else if (redirection)
			redirection = false;
		else
			count++;
		i++;
	}
	return (count);
}

char	**ft_command_args(char **split)
{
	int		i;
	int		j;
	bool	redirection;
	char	**split_arg;

	split_arg = malloc(sizeof(char *) * ft_count_args(split));
	if (split_arg == NULL)
		return (NULL);
	i = 0;
	j = 0;
	redirection = false;
	while (split[i] != NULL)
	{
		if (split[i][0] == '<' || split[i][0] == '>')
		{
			if (ft_strlen(split[i]) == 1)
				redirection = true;
		}
		else if (redirection)
			redirection = false;
		else
		{
			split_arg[j] = ft_strdup(split[i]);
			j++;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	char **splitted = ft_minishell_split(argv[1], '|');
	while (*splitted)
	{
		printf(">%s|\n", *splitted);
		printf("Tiene %d args\n", ft_count_args(ft_minishell_split(*splitted, ' ')));
		splitted++;	
	}
}