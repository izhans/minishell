/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:42:27 by isastre-          #+#    #+#             */
/*   Updated: 2025/06/17 19:45:49 by isastre-         ###   ########.fr       */
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
