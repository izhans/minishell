/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:08:21 by isastre-          #+#    #+#             */
/*   Updated: 2025/09/02 18:10:42 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @returns exit status code
 */
int	ft_process(t_minishell *mini, t_list *cmds)
{
	int			exit_status; // TODO delete and use mini.exit_status
	t_list		*current;
	t_command	*cmd;
	char		**envp;

	current = cmds;
	envp = ft_str_list_to_str_array(mini->envp); // update envp
	while (current)
	{
		// TODO pipes + redirections
		cmd = current->content;
		// check built-in
			// true
				// call built-in
			// false
				cmd->path = ft_get_cmd_executable(envp, cmd); // search path
				ft_exec_cmd(cmd, envp, &exit_status); // exec cmd
		// free cmd
		current = current->next; // next cmd
	}
	return exit_status; // return last exit_status
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
		printf("[%s]\n", cmd->path);
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
