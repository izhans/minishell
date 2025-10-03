/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:08:21 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/03 11:50:55 by ralba-ji         ###   ########.fr       */
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
	{
		mini->pids = malloc(sizeof(pid_t) * mini->line->cmd_number);
		if (mini->pids == NULL)
		{
			perror(PERROR_MALLOC);
			ft_minishell_exit(mini, EXIT_FAILURE);
		}
		ft_create_pipes(mini);
		ft_process_pipeline(mini, cmds);
		ft_close_pipes(mini);
		ft_wait_pids(mini->pids, mini);
	}
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
	{
		ft_dup2_redir(mini, cmd, true);
		ft_dup2_redir(mini, cmd, false);
		ft_exec_cmd(mini, cmd);
	}
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
	int			i;

	i = 0;
	while (cmds)
	{
		cmd = cmds->content;
		mini->pids[i] = fork();
		if (mini->pids[i] == FORK_ERROR)
		{
			perror(PERROR_FORK);
			mini->exit_status = EXIT_FAILURE;
		}
		else if (mini->pids[i] == FORK_CHILD)
		{
			ft_connect_pipes_and_redirections(mini, cmd, i);
			ft_close_pipes(mini);
			if (ft_is_built_in(cmd))
				ft_run_built_in(mini, cmd);
			else
				ft_exec_cmd(mini, cmd);
		}
		cmds = cmds->next;
		i++;
	}
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

	signal_setup_child();
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
	ft_minishell_exit(mini, exit_status);
}
