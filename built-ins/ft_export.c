/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:32:36 by isastre-          #+#    #+#             */
/*   Updated: 2025/10/02 20:06:33 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_export_print(t_minishell *mini);

void	ft_export(t_minishell *mini, t_command *cmd)
{
	if (cmd->args->next == NULL)
		return (mini->exit_status = 0, ft_export_print(mini));
	
}

static void	ft_export_print(t_minishell *mini)
{
	t_list	*current;
	char	*var_name;

	current = mini->envp;
	while (current)
	{
		var_name = ft_substr(current->content, 0,
				ft_word_name_len(current->content));
		if (var_name == NULL)
			ft_minishell_exit(mini, EXIT_FAILURE);
		printf("%s %s=\"%s\"\n", EXPORT_PRINT_PREFIX, var_name,
			ft_get_env_var_content(mini, var_name));
		free(var_name);
		current = current->next;
	}
}
