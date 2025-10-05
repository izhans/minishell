/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralba-ji <ralba-ji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:11:32 by ralba-ji          #+#    #+#             */
/*   Updated: 2025/10/05 21:47:58 by ralba-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_change_directory(t_minishell *mini, t_list *args);
static void	ft_update_env_cd(t_minishell *mini, char *last_wd, char *to_set);
static void	ft_envp_modify_value(t_minishell *mini,
				t_envp *envp, char *to_set);

void	ft_cd(t_minishell *mini, t_command *cmd)
{
	char		last_wd[PATH_MAX];
	char		new_wd[PATH_MAX];
	char const	*cd_parts[] = {NULL, "/", cmd->args->next->content, NULL};

	if (ft_lstsize(cmd->args->next) > 1)
		return (mini->exit_status = EXIT_FAILURE,
			ft_putendl_fd(BUILTIN_ERROR_ARGS_CD, STDERR_FILENO));
	if (getcwd(last_wd, PATH_MAX) == NULL)
	{
		mini->exit_status = EXIT_FAILURE;
		ft_strlcpy(last_wd, mini->pwd, ft_strlen(mini->pwd) + 1);
	}
	if (!ft_change_directory(mini, cmd->args->next))
		return ;
	free(mini->pwd);
	if (getcwd(new_wd, PATH_MAX) == NULL)
	{
		mini->exit_status = EXIT_FAILURE;
		ft_putendl_fd(BUILTIN_ERROR_GETCWD, STDERR_FILENO);
		cd_parts[0] = last_wd;
		mini->pwd = ft_joinstrs(cd_parts);
	}
	else
		mini->pwd = ft_strdup(new_wd);
	ft_update_env_cd(mini, last_wd, new_wd);
}

static char	*ft_change_directory(t_minishell *mini, t_list *args)
{
	char	*to_set;

	if (!args)
	{
		to_set = ft_get_env_var_content(mini, "HOME");
		if (to_set == NULL)
		{
			mini->exit_status = EXIT_FAILURE;
			return (ft_putendl_fd(BUILTIN_ERROR_HOME_CD, STDERR_FILENO), NULL);
		}
	}
	else
		to_set = args->content;
	if (chdir(to_set) != 0)
	{
		perror(PERROR_CD);
		mini->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	return (to_set);
}

static void	ft_update_env_cd(t_minishell *mini, char *last_wd, char	*to_set)
{
	t_envp	*pwd_node;
	t_envp	*oldpwd_node;

	if (!mini->pwd)
	{
		perror(PERROR_MALLOC);
		ft_minishell_exit(mini, EXIT_FAILURE);
	}
	pwd_node = ft_get_envp_var(mini->tenvp, "PWD");
	oldpwd_node = ft_get_envp_var(mini->tenvp, "OLDPWD");
	if (pwd_node)
	{
		ft_envp_modify_value(mini, pwd_node, to_set);
		if (oldpwd_node)
			ft_envp_modify_value(mini, oldpwd_node, last_wd);
	}
	else
		ft_remove_envp_var(&mini->tenvp, oldpwd_node);
}

static void	ft_envp_modify_value(t_minishell *mini, t_envp *envp, char *to_set)
{
	if (envp->value)
		free(envp->value);
	envp->value = ft_strdup(to_set);
	if (!envp->value)
		ft_minishell_exit(mini, EXIT_FAILURE);
}
