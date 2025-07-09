/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:29:06 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/09 19:33:22 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_process_command(char *split, t_commmand *command);
t_commmand	*ft_command_parser(char **split);
char		**ft_command_args(char **split);
int			ft_count_args(char **split);
char		*ft_command_redirection(char **split, char redirection);

/**
 *	@brief parses the received line.
 *	@param line Receives a non-null not empty line.
 *	@returns an allocated t_line struct with populated info.
*/
t_line	*ft_parse(char *line)
{
	t_line *parsed;

	parsed = malloc(sizeof(t_line));
	if (parsed == NULL)
		return (NULL);
	parsed->line = line;
	parsed->splited = ft_minishell_split(line, '|');
	parsed->cmds = ft_command_parser(parsed->splited);
	parsed->cmd_number = ft_str_array_len(parsed->splited);
	printf("Numero de comandos: %d\n", parsed->cmd_number);
	return (parsed);
}

/**
 * @brief parses all the commands on a line
 * @param split a line splitted on the pipes (|)
 * @returns an array of the parsed t_commands from the line
 */
t_commmand *ft_command_parser(char **split)
{
	t_commmand	*command;
	int			i;

	command = calloc(sizeof(t_commmand), (ft_str_array_len(split) + 1));
	if (command == NULL)
		return (NULL);
	i = 0;
	while (split[i] != NULL)
	{
		ft_process_command(split[i], &command[i]);
		i++;
	}
	return (command);
}

/**
 * @brief parses a command data into a t_command struct
 * @param split a command call (cmd + infile/outfile + args...)
 * @param command the struct to populate
 */
void ft_process_command(char *split, t_commmand *command)
{
	char	**splitcmd;

	splitcmd = ft_minishell_split(split, ' ');
	
	command->args = ft_command_args(splitcmd);
	command->path = NULL;
	command->infile = ft_command_redirection(splitcmd, '<');
	command->outfile = ft_command_redirection(splitcmd, '>');
	
	ft_free_str_array(splitcmd);
}

/**
 * @brief parses the command arguments, avoiding counting redirections
 * @param split splitted command by space
 * @returns splitted command real arguments
 */
char	**ft_command_args(char **split)
{
	int		i;
	int		j;
	bool	redirection;
	char	**split_arg;

	split_arg = malloc(sizeof(char *) * (ft_count_args(split) + 1));
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
	split_arg[j] = NULL;
	return (split_arg);
}

/**
 * @brief counts the number of real args, avoiding counting redirections
 * @param split the cmd data splitted
 * @returns the number of real cmd args
 */
int		ft_count_args(char **split)
{
	int		i;
	int		count;
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

/**
 * @brief founds the file next to the given redirection
 * @param redirection oufile (>) or infile (<)
 * @returns an allocated string with the filename or NULL if the filename isnt found
 */
char	*ft_command_redirection(char **split, char redirection)
{
	int		i;
	bool	found;
	
	i = 0;
	found = false;
	while(split[i] != NULL)
	{
		if (split[i][0] == redirection)
		{
			if (ft_strlen(split[i]) == 1)
				found = true;
			else
				return (ft_strdup(&split[i][1]));
		}
		else if (found)
			return (ft_strdup(split[i]));
		i++;
	}
	return (NULL);
}

/*
int main(int argc, char **argv)
{
	char **splitted = ft_minishell_split(argv[1], '|');
	while (*splitted)
	{
		printf(">%s|\n", *splitted);
		printf("Tiene %d args\n", ft_count_args(ft_minishell_split(*splitted, ' ')));
		splitted++;	
	}
}*/