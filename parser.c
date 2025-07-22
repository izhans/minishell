/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:29:06 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/07/22 14:52:29 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_process_command(char *split, t_commmand **command);
t_commmand	**ft_command_parser(char **split);
char		**ft_command_args(char **split);
int			ft_count_args(char **split);
char		*ft_command_redirection(char **split, char *redirection);

bool	ft_has_redirection(char *str, size_t *length);
bool	ft_has_simple_redirection(char *str);
bool	ft_has_double_redirection(char *str);

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
t_commmand **ft_command_parser(char **split)
{
	t_commmand	**commands;
	int			i;

	commands = calloc(sizeof(t_commmand *), (ft_str_array_len(split) + 1));
	if (commands == NULL)
		return (NULL);
	i = 0;
	while (split[i] != NULL)
	{
		ft_process_command(split[i], &commands[i]);
		if (commands[i] == NULL)
		{
			// TODO: liberar todo.
			return (NULL);
		}
		i++;
	}
	commands[i] = NULL;
	return (commands);
}

/**
 * @brief parses a commands data into a t_command struct
 * @param split a commands call (cmd + infile/outfile + args...)
 * @param commands the struct to populate
 */
void ft_process_command(char *split, t_commmand **command)
{
	char	**splitcmd;

	splitcmd = ft_minishell_split(split, ' ');
	
	*command = calloc(sizeof(t_commmand), 1);
	if (command == NULL)
		return;
	(*command)->args = ft_command_args(splitcmd);
	(*command)->path = NULL;
	(*command)->infile = ft_command_redirection(splitcmd, "<");
	(*command)->outfile = ft_command_redirection(splitcmd, ">");
	(*command)->here_doc = ft_command_redirection(splitcmd, "<<");
	(*command)->outfile_append = ft_command_redirection(splitcmd, ">>");

	printf("<:%s >:%s <<:%s >>:%s\n", (*command)->infile, (*command)->outfile, (*command)->here_doc, (*command)->outfile_append);
	
	ft_free_str_array(splitcmd);
}

/**
 * @brief parses the commands arguments, avoiding counting redirections
 * @param split splitted commands by space
 * @returns splitted commands real arguments
 */
char	**ft_command_args(char **split)
{
	int		i;
	int		j;
	size_t	redirection_length;
	bool	redirection;
	char	**split_arg;

	split_arg = malloc(sizeof(char *) * (ft_count_args(split) + 1));
	if (split_arg == NULL)
		return (NULL);
	i = 0;
	j = 0;
	redirection_length = 0;
	redirection = false;
	while (split[i] != NULL)
	{
		if (ft_has_redirection(split[i], &redirection_length))
		{
			if (ft_strlen(split[i]) == redirection_length)
				redirection = true;
		}
		else if (redirection)
			redirection = false;
		else if (!ft_is_empty(split[i]))
		{
			split_arg[j] = ft_strdup(split[i]);
			printf("real arg %d: [%s]\n", j, split_arg[j]);
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
	size_t	redirection_length;
	bool	redirection;

	i = 0;
	count = 0;
	redirection = false;
	redirection_length = 0;
	while (split[i] != NULL)
	{
		printf("i: %d [%s]\n", i, split[i]);
		if (ft_has_redirection(split[i], &redirection_length))
		{
			if (ft_strlen(split[i]) == redirection_length)
				redirection = true;
		}
		else if (redirection)
			redirection = false;
		else if (!ft_is_empty(split[i]))
			count++;
		i++;
	}
	printf("args %d\n", count);
	return (count);
}

/**
 * @brief founds the file next to the given redirection
 * @param redirection oufile (>), outfile append mode (>>), infile (<) or heredoc (<<)
 * @returns an allocated string with the filename or NULL if the filename isnt found
 */
char	*ft_command_redirection(char **split, char *redirection)
{
	int		i;
	bool	found;
	size_t	redirection_len;
	
	i = 0;
	found = false;
	redirection_len = ft_strlen(redirection);
	while(split[i] != NULL)
	{
		if (ft_strncmp(split[i], redirection, redirection_len) == 0)
		{
			if (ft_strlen(split[i]) != redirection_len && split[i][redirection_len] != redirection[0])
				return (ft_strdup(&split[i][redirection_len]));
			else if (ft_strlen(split[i]) == redirection_len)
				found = true;
		}
		else if (found)
			return (ft_strdup(split[i]));
		i++;
	}
	return (NULL);
}

bool	ft_has_redirection(char *str, size_t *length)
{
	if (ft_has_double_redirection(str))
		return (*length = 2, true);
	if (ft_has_simple_redirection(str))
		return (*length = 1, true);
	return (*length = 0, false);
}

bool	ft_has_simple_redirection(char *str)
{
	return (str[0] == '<' || str[0] == '>');
}

bool	ft_has_double_redirection(char *str)
{
	return (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0);
}
