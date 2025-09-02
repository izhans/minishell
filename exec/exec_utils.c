/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:20:23 by isastre-          #+#    #+#             */
/*   Updated: 2025/08/29 21:34:33 by isastre-         ###   ########.fr       */
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
