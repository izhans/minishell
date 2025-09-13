/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:08:21 by isastre-          #+#    #+#             */
/*   Updated: 2025/09/13 20:51:09 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_process_one_cmd(t_command *cmd, char **envp, int *exit_status);
static void	ft_process_pipeline(t_list *cmds, char **envp, int *exit_status);
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
		ft_process_pipeline(cmds, envp, &(mini->exit_status));
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
static void	ft_process_pipeline(t_list *cmds, char **envp, int *exit_status)
{
	t_command	*cmd;
	pid_t		pid;

	while (cmds)
	{
		// TODO pipes + redirections
		cmd = cmds->content;
		pid = fork();
		if (pid < 0) // error
			*exit_status = EX_OSERR;
		else if (pid == 0) // child
		{
			// check built-in
			if (ft_is_built_in(cmd)) // true
				ft_run_built_in(cmd, exit_status); // call built-in
			else // false
				ft_exec_cmd(cmd, envp, exit_status); // exec cmd
		}
		else // parent
		{
			waitpid(pid, exit_status, 0);
			if (WIFEXITED(*exit_status))
				*exit_status = WEXITSTATUS(*exit_status); // transform the exit status code
		}
		cmds = cmds->next; // next cmd
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
	(void)exit_status;
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
