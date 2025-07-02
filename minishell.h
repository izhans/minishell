/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:42:27 by isastre-          #+#    #+#             */
/*   Updated: 2025/07/02 18:00:37 by ralba-ji         ###   ########.fr       */
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

typedef struct s_command
{
	char	*path; // binary route
	char	**args; // cmd args (includes cmd name)
	char	***env; // enviroment vars // ? might not use?
}	t_commmand;

typedef struct s_line
{
	char		*line; // TODO delete later
	char		**splited;
	char		*infile;
	char		*outfile;
	int			cmd_number;
	t_commmand	*cmds;
}	t_line;

#endif
