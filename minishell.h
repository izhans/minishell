/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 02:14:56 by isastre-          #+#    #+#             */
/*   Updated: 2025/07/25 04:12:01 by ralba-ji         ###   ########.fr       */
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

typedef enum e_redir_type
{
	INFILE=0,
	OUTFILE=1,
	OUTFILE_APPEND=2,
	HERE_DOC=3
}	t_redir_type;

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

//Struct t_minishell

t_minishell	*ft_create_t_minishell(char *envp[]);
void		ft_free_t_minishell(t_minishell *mini);
t_list		*ft_str_array_to_str_lst(char *envp[]);

//Struct t_line
t_line		*ft_create_t_line(t_minishell *mini, char *str);
void		ft_free_line(t_line *line);
//Struct t_command
void		ft_free_command(void *content);

//Utils
void		ft_minishell_exit(t_minishell *mini);
void		ft_comma_check(char *comma, char line_char);

//Parser
t_line		*ft_parser(t_minishell *mini, char	*line);
#endif
