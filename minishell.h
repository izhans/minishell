/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 02:14:56 by isastre-          #+#    #+#             */
/*   Updated: 2025/07/25 02:41:06 by isastre-         ###   ########.fr       */
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

typedef struct s_line		t_line;
typedef struct s_command	t_command;
typedef struct s_redir		t_redir;
typedef enum e_redir_type	t_redir_type;

typedef struct s_minishell
{
	t_list	*envp;
	int		exit_status; // last exit status
	t_line	*line;
}	t_minishell;

typedef struct s_line
{
	char	*line;
	int		cmd_number;
	t_list	*cmds; // list of t_command wrappers
}	t_line;

typedef struct s_command // is contained into a t_list
{
	char	*path;
	t_list	*args;
	t_list	*redir; // list of t_redir wrappers
}	t_command;

typedef struct s_redir // is contained into a t_list
{
	t_redir_type	type;
	char			*filename;
}	t_redir;

typedef enum e_redir_type
{
	INFILE=0,
	OUTFILE=1,
	OUTFILE_APPEND=2,
	HERE_DOC=3
}	t_redir_type;

#endif
