/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:32:36 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/05 20:01:57 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_export_print(t_minishell *mini);
static void	ft_process_arg(t_minishell *mini, char *key, char *value);

void	ft_export(t_minishell *mini, t_command *cmd)
{
	t_list	*args;
	char	*key;
	char	*value;

	args = cmd->args->next;
	mini->exit_status = 0;
	if (!args)
		return (ft_export_print(mini));
	while (args)
	{
		ft_split_key_value(args->content, &key, &value);
		ft_process_arg(mini, key, value);
		args = args->next;
	}
}

static void	ft_export_print(t_minishell *mini)
{
	t_envp	*current;

	current = mini->tenvp;
	while (current)
	{
		if (current->value)
			printf("%s %s=\"%s\"\n", EXPORT_PRINT_PREFIX,
				current->key, current->value);
		else
			printf("%s %s\n", EXPORT_PRINT_PREFIX, current->key);
		current = current->next;
	}
}

static void	ft_process_arg(t_minishell *mini, char *key, char *value)
{
	t_envp	*var;

	if (!ft_is_valid_identifier(key))
	{
		ft_putendl_fd(BUILTIN_ERROR_IDENTIFIER_EXPORT, STDERR_FILENO);
		mini->exit_status = 1;
		return ;
	}
	var = ft_get_envp_var(mini->tenvp, key);
	if (var && value)
	{
		free(var->value);
		var->value = value;
	}
	else if (var == NULL)
	{
		var = ft_envp_new(key, value);
		if (var == NULL)
		{
			perror(PERROR_MALLOC);
			ft_minishell_exit(mini, EXIT_FAILURE);
		}
		ft_envp_add_back(&mini->tenvp, var);
	}
}
