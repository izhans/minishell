/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:08:21 by isastre-          #+#    #+#             */
/*   Updated: 2025/09/18 17:50:48 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_process_one_cmd(t_command *cmd, char **envp, int *exit_status);
static void	ft_process_pipeline(t_minishell *mini, t_list *cmds, char **envp, int *exit_status);
static void	ft_run_built_in(t_command *cmd, int *exit_status);
static void	ft_exec_cmd(t_command *cmd, char **envp, int *exit_status);

/**
 * @brief evaluates and chooses the one cmd or the pipeline flow
 * @param mini current execution data
 * @param cmds list of the cmds to execute
 */
void	ft_process(t_minishell *mini)
{
	char		**envp;
	t_list		*cmds;

	cmds = mini->line->cmds;
	envp = ft_str_list_to_str_array(mini->envp); // update envp
	if (mini->line->cmd_number == 1)
		ft_process_one_cmd(cmds->content, envp, &(mini->exit_status));
	else
		ft_process_pipeline(mini, cmds, envp, &(mini->exit_status));
	ft_free_str_array(envp);
}

/**
 * @brief chooses how to execute the cmd depending if its a built-in or not
 * @param cmd the cmd to execute
 * @param envp the envp (for execve)
 * @param exit_status a pointer to the exit status code
 */
static void	ft_process_one_cmd(t_command *cmd, char **envp, int *exit_status)
{
	pid_t	pid;

	if (ft_is_built_in(cmd))
		return ft_run_built_in(cmd, exit_status);
	pid = fork();
	if (pid < 0) // error
		*exit_status = EX_OSERR;
	else if (pid == 0) // child
		ft_exec_cmd(cmd, envp, exit_status);
	else // parent
	{
		waitpid(pid, exit_status, 0);
		if (WIFEXITED(*exit_status))
			*exit_status = WEXITSTATUS(*exit_status); // transform the exit status code
	}
}

/**
 * @brief processes a cmd pipeline
 * @param cmds a list with all the cmds at the pipeline
 * @param envp the envp (for execve)
 * @param exit_status a pointer to the exit status code
 */
static void	ft_process_pipeline(t_minishell *mini, t_list *cmds, char **envp, int *exit_status)
{
	t_command	*cmd;
	pid_t		*pids;
	int			(*pipes)[2];
	int			i;

	pipes = NULL;
	pids = malloc(sizeof(pid_t) * mini->line->cmd_number);//TODO error
	ft_create_pipes(&pipes, mini->line->cmd_number);
	i = 0;
	while (cmds)
	{
		// TODO redirections
		cmd = cmds->content;
		pids[i] = fork();
		if (pids[i] < 0) // error
			*exit_status = EX_OSERR;
		else if (pids[i] == 0) // child
		{
			ft_connect_pipes(pipes, i, mini->line->cmd_number);
			ft_close_pipes(pipes, mini->line->cmd_number);
			// check built-in
			if (ft_is_built_in(cmd)) // true
				ft_run_built_in(cmd, exit_status); // call built-in
			else // false
				ft_exec_cmd(cmd, envp, exit_status); // exec cmd
		}
		
		cmds = cmds->next; // next cmd
		i++;
	}
	
	ft_close_pipes(pipes, mini->line->cmd_number);
	// ft_free_pipes(pipes);
	i = 0;
	while (i < mini->line->cmd_number)
	{
		waitpid(pids[i], exit_status, 0);
		if (WIFEXITED(*exit_status))
			*exit_status = WEXITSTATUS(*exit_status); // transform the exit status code
		i++;
	}
}

/**
 * @brief TODO: redirects a built-in to its own function execution
 * @param cmd the built-in cmd data
 * @param exit_status a pointer to the exit status code
 */
static void	ft_run_built_in(t_command *cmd, int *exit_status)
{
	(void) exit_status;
	// TODO pseudo-switch with built-in options
	printf("running built-in %s\n", (char *) cmd->args->content);
}

/**
 * @brief execs one cmd and updates the exit status code
 * @param cmd the cmd to execute
 * @param envp the envp (for execve)
 * @param exit_status a pointer to the exit status code
 */
static void	ft_exec_cmd(t_command *cmd, char **envp, int *exit_status)
{
	(void) exit_status; // ! TODO delete, no es necesario porque lo recoge el padre
	char	**cmd_args_array;

	cmd_args_array = ft_str_list_to_str_array(cmd->args);
	// TODO check ft_str_list_to_str_array error

	cmd->path = ft_get_cmd_executable(envp, cmd); // search path
	if (cmd->path == NULL)
		exit(127); // cmd not found // TODO free all before exit
	execve(cmd->path, cmd_args_array, envp);
	exit(126); // cmd invoked cannot execute // TODO free all before exit
	
	ft_free_str_array(cmd_args_array);
}
