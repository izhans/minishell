/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 02:14:56 by isastre-          #+#    #+#             */
/*   Updated: 2025/09/26 16:54:03 by isastre-         ###   ########.fr       */
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
# include <sysexits.h>

# include "libft/libft.h"

# define SIMPLE_COMMA '\''
# define DOUBLE_COMMA '"'
# define PIPE '|'
# define ERROR_MSG_REDIRECTION "Invalid input: invalid redirection or filename for redirection\n"
# define ERROR_MSG_PIPES "Invalid input: missing command.\n"
# define PERROR_MALLOC "Error malloc: "
# define PERROR_DUP2 "Error dup2: "
# define PERROR_PIPE "Error pipe: "
# define PERROR_FORK "Error fork: "

# define READ_END STDIN_FILENO
# define WRITE_END STDOUT_FILENO
# define FORK_CHILD 0
# define FORK_ERROR -1
# define DUP2_ERROR -1
# define EX_CANNOT_INVOKE_CMD 126
# define EX_CMD_NOT_FOUND 127

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

typedef enum e_type_arg
{
	NONE = 0,
	ARG=1,
	IN=2,
	OUT=3,
	OUT_APPEND=4,
	HERE=5,
}	t_type_arg;

typedef struct s_minishell
{
	t_list	*envp;
	int		exit_status; // last exit status
	t_line	*line;
	char	**envp_array;
	pid_t	*pids;
	int		(*pipes)[2];
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
	char	*cmd_str;
}	t_command;

typedef struct s_redir // is contained into a t_list
{
	t_redir_type	type;
	char			*filename;
}	t_redir;

//Struct t_minishell
t_minishell	*ft_create_t_minishell(char *envp[]);
void		ft_free_t_minishell(t_minishell *mini);
void		ft_free_t_minishell_execution(t_minishell *mini);
t_list		*ft_str_array_to_str_lst(char *envp[]);
char		**ft_str_list_to_str_array(t_list *list);

//Struct t_line
t_line		*ft_create_t_line(t_minishell *mini, char *str);
void		ft_free_line(t_line *line);

//Struct t_command
t_command	*ft_create_t_command(t_minishell *mini);
void		ft_free_command(void *content);

//Struct t_redir
t_redir		*ft_create_t_redir(char *line, int len, t_type_arg type);
void		ft_free_redir(void *content);

//Utils
void		ft_minishell_exit(t_minishell *mini, int exit_status);
bool		ft_is_empty(char *string);

//Parser
t_line		*ft_parser(t_minishell *mini, char	*line);
t_list		*ft_add_to_list(t_command **cmd, char *line,
				int len, t_type_arg *type);
void		ft_next_checker(t_type_arg *type, char comma, char line_char);
void		ft_comma_check(char *comma, char line_char);
bool		ft_is_redir(int c);

//Expand and clear
void		ft_expand_clear(t_minishell *mini, t_line **line);
void		ft_expand_clear_var(t_minishell *mini, void *content, bool is_arg);
char		*ft_expand_var(t_minishell *mini, char **str, bool is_heredoc);
char		*ft_clear_var(t_minishell *mini, char **str);

//Env utils
char		*ft_word(t_minishell *mini, char *str);
int			ft_word_name_len(char *str);
int			ft_word_len(t_minishell *mini, char *str);
// exec + exec utils
void		ft_process(t_minishell *mini);
char		*ft_get_cmd_executable(char **envp, t_command *cmd);
bool		ft_is_built_in(t_command *cmd);
void		ft_wait_pids(pid_t *pids, t_minishell *mini);
// pipes
void		ft_create_pipes(t_minishell *mini);
void		ft_connect_pipes_and_redirections(t_minishell *mini, int i);
void		ft_close_pipes(t_minishell *mini);

//Validator
bool		ft_validate(t_minishell *mini, t_line *line);

#endif
