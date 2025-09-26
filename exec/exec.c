/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:08:21 by isastre-          #+#    #+#             */
/*   Updated: 2025/09/26 13:27:52 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_process_one_cmd(t_minishell *mini, t_command *cmd);
static void	ft_process_pipeline(t_minishell *mini, t_list *cmds);
static void	ft_run_built_in(t_minishell *mini, t_command *cmd);
static void	ft_exec_cmd(t_minishell *mini, t_command *cmd);

/**
 * @brief evaluates and chooses the one cmd or the pipeline flow
 * @param mini current execution data
 */
void	ft_process(t_minishell *mini)
{
	t_list		*cmds;

	cmds = mini->line->cmds;
	mini->envp_array = ft_str_list_to_str_array(mini->envp);
	if (mini->line->cmd_number == 1)
		ft_process_one_cmd(mini, cmds->content);
	else
		ft_process_pipeline(mini, cmds);
}

/**
 * @brief chooses how to execute the cmd depending if its a built-in or not
 * @param mini current execution data
 * @param cmd the cmd to execute
 */
static void	ft_process_one_cmd(t_minishell *mini, t_command *cmd)
{
	pid_t	pid;

	if (ft_is_built_in(cmd))
		return (ft_run_built_in(mini, cmd));
	pid = fork();
	if (pid == FORK_ERROR)
	{
		perror(PERROR_FORK);
		mini->exit_status = EXIT_FAILURE;
	}
	else if (pid == FORK_CHILD)
		ft_exec_cmd(mini, cmd);
	else
		ft_wait_pids(&pid, mini);
}

/**
 * @brief processes a cmd pipeline
 * @param mini current execution data
 * @param cmds a list with all the cmds at the pipeline
 */
static void	ft_process_pipeline(t_minishell *mini, t_list *cmds)
{
	t_command	*cmd;
	pid_t		*pids;
	int			(*pipes)[2];
	int			i;

	pipes = NULL;
	pids = malloc(sizeof(pid_t) * mini->line->cmd_number);//TODO error
	ft_create_pipes(mini, &pipes, mini->line->cmd_number);
	i = 0;
	while (cmds)
	{
		// TODO redirections
		cmd = cmds->content;
		pids[i] = fork();
		if (pids[i] == FORK_ERROR)
		{
			perror(PERROR_FORK);
			mini->exit_status = EXIT_FAILURE;
		}
		else if (pids[i] == FORK_CHILD)
		{
			ft_connect_pipes(pipes, i, mini->line->cmd_number);
			ft_close_pipes(pipes, mini->line->cmd_number);
			if (ft_is_built_in(cmd))
				ft_run_built_in(mini, cmd);
			else
				ft_exec_cmd(mini, cmd);
		}
		cmds = cmds->next;
		i++;
	}
	
	ft_close_pipes(pipes, mini->line->cmd_number);
	ft_wait_pids(pids, mini);
	ft_free_pipes(pipes, mini->line->cmd_number);
	free(pids);
}

/**
 * @brief TODO: redirects a built-in to its own function execution
 * @param mini current execution data
 * @param cmd the built-in cmd data
 */
static void	ft_run_built_in(t_minishell *mini, t_command *cmd)
{
	(void) mini;
	// TODO pseudo-switch with built-in options
	printf("running built-in %s\n", (char *) cmd->args->content);
}

/**
 * @brief execs one cmd and updates the exit status code
 * @param mini current execution data
 * @param cmd the cmd to execute
 */
static void	ft_exec_cmd(t_minishell *mini, t_command *cmd)
{
	int		exit_status;
	char	**cmd_args_array;

	cmd_args_array = ft_str_list_to_str_array(cmd->args);
	if (cmd_args_array == NULL)
	{
		perror(PERROR_MALLOC);
		ft_minishell_exit(mini, EXIT_FAILURE);
	}
	cmd->path = ft_get_cmd_executable(mini->envp_array, cmd);
	if (cmd->path == NULL)
		exit_status = EX_CMD_NOT_FOUND;
	else
	{
		execve(cmd->path, cmd_args_array, mini->envp_array);
		exit_status = EX_CANNOT_INVOKE_CMD;
	}
	ft_free_str_array(cmd_args_array);
	ft_free_t_minishell(mini);
	exit(exit_status);
}
