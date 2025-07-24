
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

typedef enum e_redir
{
	INFILE=0,
	OUTFILE=1,
	OUTFILE_APPEND=2,
	HERE_DOC=3
}	t_redir;

typedef struct s_list_str
{
	char				*content;
	struct s_list_str	*next;
}	t_list_str;

typedef struct s_list_redir
{
	t_redir				type;
	char				*filename;
	struct s_list_redir	*next;
}	t_list_redir;


typedef struct s_command
{
	char					*path;
	t_list_str				*args;
	t_list_redir			*redir;
	struct s_command		*next;
}	t_command;


typedef struct s_line
{
	char		*line;
	int			cmd_number;
	t_command	*cmds;
}	t_line;

typedef struct s_minishell
{
	char	**envp;
	int		exit_status; // last exit status
	t_line	*line;
}	t_minishell;

#endif