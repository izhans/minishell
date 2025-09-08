/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:08:21 by isastre-          #+#    #+#             */
/*   Updated: 2025/09/08 21:27:25 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_process_one_cmd(t_command *cmd, char **envp);
static int	ft_process_pipeline(t_list *cmds, char **envp);
static int	ft_run_built_in(t_command *cmd);

/**
 * @brief evaluates and chooses the one cmd or the pipeline flow
 * @returns exit status code
 */
int	ft_process(t_minishell *mini, t_list *cmds)
{
	int			exit_status; // TODO delete and use mini.exit_status
	char		**envp;

	envp = ft_str_list_to_str_array(mini->envp); // update envp
	if (mini->line->cmd_number == 1)
		return ft_process_one_cmd(mini->line->cmds->content, envp), exit_status;
	ft_process_pipeline(cmds, envp);
	
	return exit_status; // return last exit_status
}

/**
 * @brief chooses how to execute the cmd depending if its a built-in or not
 * @returns exit status code
 */
static int	ft_process_one_cmd(t_command *cmd, char **envp)
{
	int	exit_status; // TODO delete and use mini.exit_status

	if (ft_is_built_in(cmd->args->content))
		return ft_run_built_in(cmd);
	ft_exec_cmd(cmd, envp, &exit_status);
	return exit_status;
}

/**
 * @brief processes a cmd with pipes 
 * @returns exit status code
 */
static int	ft_process_pipeline(t_list *cmds, char **envp)
{
	int			exit_status; // TODO delete and use mini.exit_status
	t_list		*current; // ? can delete and use directly cmds?
	t_command	*cmd;

	current = cmds;
	while (current)
	{
		// TODO pipes + redirections
		cmd = current->content;
		// check built-in
			// true
				// call built-in
			// false
				ft_exec_cmd(cmd, envp, &exit_status); // exec cmd
		// free cmd
		current = current->next; // next cmd
	}
	return exit_status;
}

static int	ft_run_built_in(t_command *cmd)
{
	// TODO pseudo-switch with built-in options
	printf("running built-in %s\n", (char *) cmd->args->content);
	return 0;
}

/**
 * @brief execs one cmd and updates the exit status code
 * @param cmd the cmd to execute
 * @param envp the envp (for execve)
 * @param exit_status a pointer to the exit status code
 */
void	ft_exec_cmd(t_command *cmd, char **envp, int *exit_status)
{
	char	**cmd_args_array;
	pid_t	pid;

	cmd_args_array = ft_str_list_to_str_array(cmd->args);
	// TODO check ft_str_list_to_str_array error
	pid = fork();
	if (pid < 0) // error
		*exit_status = EX_OSERR;
	else if (pid == 0) // child
	{
		cmd->path = ft_get_cmd_executable(envp, cmd); // search path
		if (cmd->path == NULL)
			exit(127); // cmd not found
		execve(cmd->path, cmd_args_array, envp);
		exit(126); // cmd invoked cannot execute
	}
	else // parent
	{
		waitpid(pid, exit_status, 0);
		if (WIFEXITED(*exit_status))
			*exit_status = WEXITSTATUS(*exit_status); // transform the exit status code
	}
	ft_free_str_array(cmd_args_array);
}
