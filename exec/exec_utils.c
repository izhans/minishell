/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:20:23 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/03 12:33:54 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_get_path(char **envp);

/**
 * @brief searchs the executable (binary) of a given cmd
 * @param envp the env with the PATH variable
 * @param cmd the cmd data
 * @returns the cmd executable or NULL if error or not found
 */
char	*ft_get_cmd_executable(char **envp, t_command *cmd)
{
	char		**path;
	int			i;
	char		*cmd_executable;
	char const	*cmd_parts[] = {NULL, "/", cmd->args[0].content, NULL};

	if (access(cmd->args[0].content, F_OK) == 0)
		return (ft_strdup(cmd->args[0].content));
	path = ft_get_path(envp);
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i])
	{
		cmd_parts[0] = path[i];
		cmd_executable = ft_joinstrs(cmd_parts);
		if (access(cmd_executable, F_OK) == 0)
		{
			ft_free_str_array(path);
			return (cmd_executable);
		}
		free(cmd_executable);
		i++;
	}
	ft_free_str_array(path);
	return (NULL);
}

/**
 * @brief gets the PATH variable from the envp
 * @param envp the minishell env
 */
static char	**ft_get_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

/**
 * @brief checks if a cmd is built-in or not
 * @param cmd the cmd data
 * @returns true if the cmd is built-in, false if not
 */
bool	ft_is_built_in(t_command *cmd)
{
	const char	*cmd_name = cmd->args->content;
	int			i;
	const char	*built_ins[] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};

	i = 0;
	while (built_ins[i])
	{
		if (ft_strcmp((char *) cmd_name, (char *) built_ins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief wait for all the processes with the pids and
 */
void	ft_wait_pids(pid_t *pids, t_minishell *mini)
{
	int	i;

	i = 0;
	signal(SIGINT, SIG_IGN);
	while (i < mini->line->cmd_number)
	{
		waitpid(pids[i], &mini->exit_status, 0);
		if (WIFEXITED(mini->exit_status))
			mini->exit_status = WEXITSTATUS(mini->exit_status);
		else if (WIFSIGNALED(mini->exit_status))
			mini->exit_status = 128 + WTERMSIG(mini->exit_status);
		i++;
	}
	signal_check(mini->exit_status);
}
