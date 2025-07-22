/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:42:27 by isastre-          #+#    #+#             */
/*   Updated: 2025/07/22 14:42:02 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>

# include <stdbool.h>

# include "libft/libft.h"

# define SIMPLE_COMMA '\''
# define DOUBLE_COMMA '"'
# define PIPE '|'

typedef struct s_command
{
	char	*path; // binary route
	char	**args; // cmd args (includes cmd name)
	char	***env; // enviroment vars // ? might not use?
	char	*infile;
	char	*outfile;
	char	*here_doc;
	char	*outfile_append;
}	t_commmand;

typedef struct s_line
{
	char		*line;
	char		**splited;
	int			cmd_number;
	t_commmand	**cmds;
}	t_line;

char	**ft_minishell_split(char *line, char delimiter);
t_line	*ft_parse(char *line);
void	ft_free_tline(t_line *line);
bool	ft_validator(t_line *parsed);

//Utils:
void	ft_comma_check(char *comma, char line_char);
bool	ft_is_empty(char *string);

#endif
